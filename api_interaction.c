#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>  // Include cJSON for JSON parsing
#include <sys/stat.h>     // Include for checking directory existence
#include <unistd.h>       // Include for access()

#define API_KEY "a37a9dd4792a402cbc5100355240708"  // Add your API key here
#define BASE_URL "http://api.weatherapi.com/v1/current.json?key=" API_KEY "&q="

// Structure to hold the API response
struct ApiResponse {
    char *content;
    size_t size;
    size_t capacity;  // Track allocated capacity
};

// Initial block size and resizing factor for dynamic allocation
#define INITIAL_SIZE 1024  // 1 KB initial size
#define RESIZE_FACTOR 2    // Factor by which to increase memory when needed

// Function to initialize ApiResponse with a predefined block size
void initializeApiResponse(struct ApiResponse *response) {
    response->content = malloc(INITIAL_SIZE);
    if (response->content == NULL) {
        fprintf(stderr, "Error: Initial memory allocation failed\n");
        exit(1);
    }
    response->size = 0;
    response->capacity = INITIAL_SIZE;
}

// Function to resize ApiResponse memory efficiently
int resizeApiResponse(struct ApiResponse *response, size_t new_size) {
    if (new_size > response->capacity) {
        size_t new_capacity = response->capacity * RESIZE_FACTOR;
        char *new_content = realloc(response->content, new_capacity);
        if (new_content == NULL) {
            return -1;  // Memory allocation failed
        }
        response->content = new_content;
        response->capacity = new_capacity;
    }
    return 0;
}

// Function to release memory after usage
void freeApiResponse(struct ApiResponse *response) {
    free(response->content);
    response->content = NULL;
    response->size = 0;
    response->capacity = 0;
}

// Function to create and initialize an ApiResponse structure
struct ApiResponse* createApiResponse() {
    struct ApiResponse* response = malloc(sizeof(struct ApiResponse));
    if (response == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for ApiResponse\n");
        exit(1);
    }
    initializeApiResponse(response);  // Initialize with predefined block size and capacity
    return response;
}

// Function to delete an ApiResponse structure and free its memory
void deleteApiResponse(struct ApiResponse* response) {
    if (response) {
        freeApiResponse(response);  // Free the content memory inside the structure
        free(response);             // Free the structure itself
    }
}

// Callback function to handle data from the API response
static size_t WriteCallback(void *data, size_t element_size, size_t element_count, void *user_buffer) {
    size_t total_bytes = element_size * element_count;
    struct ApiResponse *api_buffer = (struct ApiResponse *)user_buffer;

    if (resizeApiResponse(api_buffer, api_buffer->size + total_bytes + 1) != 0) {
        fprintf(stderr, "Error: Insufficient memory\n");
        return 0;
    }

    memcpy(&(api_buffer->content[api_buffer->size]), data, total_bytes);
    api_buffer->size += total_bytes;
    api_buffer->content[api_buffer->size] = '\0';

    return total_bytes;
}

// Function to fetch weather data from the API
void retrieve_weather_data(const char *city) {
    CURL *curl_session;
    CURLcode response_code;

    struct ApiResponse *api_response = createApiResponse();

    char url[256];
    snprintf(url, sizeof(url), "%s%s", BASE_URL, city);  // Construct the full URL with city

    curl_global_init(CURL_GLOBAL_ALL);
    curl_session = curl_easy_init();

    if (curl_session) {
        curl_easy_setopt(curl_session, CURLOPT_URL, url);
        curl_easy_setopt(curl_session, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_session, CURLOPT_WRITEDATA, (void *)api_response);

        response_code = curl_easy_perform(curl_session);

        if (response_code != CURLE_OK) {
            fprintf(stderr, "API request failed: %s\n", curl_easy_strerror(response_code));
        } else {
            // Check if 'data' directory exists, create if not
            struct stat st = {0};
            if (stat("data", &st) == -1) {
                if (mkdir("data", 0777) != 0) {
                    perror("Error creating data directory");
                    deleteApiResponse(api_response);
                    curl_easy_cleanup(curl_session);
                    curl_global_cleanup();
                    return;
                }
            }

            // Save response data to file
            FILE *output_file = fopen("data/weather_data.txt", "a");
            if (output_file) {
                fputs(api_response->content, output_file);
                fprintf(output_file, "\n");
                fclose(output_file);
                printf("Weather data saved to weather_data.txt\n");  // Confirmation message
            } else {
                perror("Error opening file for writing");
            }
        }

        curl_easy_cleanup(curl_session);
    }

    deleteApiResponse(api_response);
    curl_global_cleanup();
}

// Function to interpret and process sensor data
void interpret_sensor_data() {
    FILE *file = fopen("data/weather_data.txt", "r");
    if (!file) {
        perror("Error opening weather_data.txt");
        return;
    }

    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    cJSON *json = cJSON_Parse(buffer);
    if (!json) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    cJSON *current = cJSON_GetObjectItem(json, "current");
    float temp_c = cJSON_GetObjectItem(current, "temp_c")->valuedouble;
    float humidity = cJSON_GetObjectItem(current, "humidity")->valuedouble;

    printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temp_c, humidity);

    // Save processed data to processed_sensor_data.txt
    FILE *processed_file = fopen("data/processed_sensor_data.txt", "a");
    if (processed_file) {
        fprintf(processed_file, "Temperature: %.2f°C, Humidity: %.2f%%\n", temp_c, humidity);
        fclose(processed_file);
    } else {
        perror("Error opening processed_sensor_data.txt");
    }

    cJSON_Delete(json);
}
