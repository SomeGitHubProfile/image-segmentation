#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define this_config_reference "this"
const Config default_config = {
    this_config_reference,
    MedianFilter_disabled,
    GaussianKernel_5x5,
    SobelKernel_5x5,
    88,
    0
};

#define number_of_params 6
const char* param_names[number_of_params] = {
    "config",
    "median filter",
    "gaussian kernel",
    "sobel kernel",
    "boundaries detection strength",
    "boundaries radius"
};
#define max_number_of_values 3
const char* param_values[number_of_params][max_number_of_values] = {
    {"this"},
    {"enabled", "disabled"},
    {"3x3", "5x5", "5x5_low_value"},
    {"3x3", "5x5"}
};
const int values[number_of_params][max_number_of_values] = {
    {0},
    {MedianFilter_enabled, MedianFilter_disabled},
    {GaussianKernel_3x3, GaussianKernel_5x5, GaussianKernel_5x5_low_value},
    {SobelKernel_3x3, SobelKernel_5x5}
};
const size_t values_length[number_of_params] = {
    0,
    2,
    3,
    2
};

char* get_name_from_path(char* path) {
    int index = 0;
    for (int i = 0; i < strlen(path); ++i) {
        if (path[i] == '/') {
            index = i + 1;
        }
    }
    return path + index;
}

int** get_config_values(Config* config) {
    int* config_values_static[number_of_params] = {
        NULL,
        &(config->median_filter),
        &(config->gaussian_kernel),
        &(config->sobel_kernel),
        &(config->boundaries_detection_strength),
        &(config->boundaries_radius)
    };
    int** config_values = malloc(number_of_params * sizeof(int*));
    for (int i = 0; i < number_of_params; ++i) {
        config_values[i] = config_values_static[i];
    }
    return config_values;
}

void print_config(Config config, FILE* const stream) {
    int** config_values = get_config_values(&config);
    fprintf(stream, "%s: %s\n", param_names[0], this_config_reference);
    for (int i = 1; i < number_of_params - 2; ++i) {
        fprintf(stream, "%s: %s\n", param_names[i], param_values[i][*config_values[i]]);
    }
    for (int i = number_of_params - 2; i < number_of_params; ++i) {
        fprintf(stream, "%s: %d\n", param_names[i], *config_values[i]);
    }
    return;
}

Config create_default_config() {
    FILE* file = fopen(default_config_name, "w");
    print_config(default_config, file);
    fclose(file);
    return default_config;
}

bool parse_string(char* line, char* param, char* value) {
    for (int i = 1; i < strlen(line) - 1; ++i) {
        if (line[i - 1] == ':' && line[i] == ' ') {
            int param_size = i - 1;
            memcpy(param, line, param_size);
            memcpy(param + param_size, "\0", 1);
            int value_begin_index = i + 1;
            int value_end_index = strlen(line) - 1;
            int value_size = value_end_index - value_begin_index;
            memcpy(value, line + value_begin_index, value_size);
            memcpy(value + value_size, "\0", 1);
            return true;
        }
    }
    return false;
}

#define max_line_length 100
Config load_config(const char* path) {
    Config config = default_config;
    FILE* file = fopen(path, "r");
    if (!file) {
        return create_default_config();
    }

    int** config_values = get_config_values(&config);

    char line[max_line_length];
    char param[max_line_length];
    char string_value[max_line_length];
    while (fgets(line, max_line_length, file) && parse_string(line, param, string_value)) {
        bool param_found = false;
        int param_index = 0;
        for (; !param_found && param_index < number_of_params; ++param_index) {
            param_found = !strcmp(param_names[param_index], param);
        }
        if (!param_found) {
            continue;
        }
        --param_index;
        switch (param_index) {
            case 0:
                if (!strcmp(get_name_from_path(path), default_config_name)
                    && strcmp(default_config_name, string_value)
                    && strcmp(this_config_reference, string_value)
                ) {
                    free(config_values);
                    fclose(file);
                    return load_config(string_value);
                }
                break;
            case 4:
            case 5:
            {
                char* end_ptr;
                unsigned char value = strtol(string_value, &end_ptr, 10);
                if (end_ptr == string_value || value < Boundaries_min_value || value > Boundaries_max_value) {
                    break;
                }
                *config_values[param_index] = value;
            }
                break;
            default:
            {
                int value_index = 0;
                bool value_found = false;
                for (; !value_found && value_index < values_length[param_index]; ++value_index) {
                    value_found = !strcmp(param_values[param_index][value_index], string_value);
                }
                if (!value_found) {
                    break;
                }
                --value_index;
                *(config_values[param_index]) = values[param_index][value_index];
            }
                break;
        }
    }
    free(config_values);
    fclose(file);
    printf("Loaded %s\n", get_name_from_path(path));
    return config;
}
