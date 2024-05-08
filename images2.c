//Authors:Brayden Vieira and Stephan Therianos
//Purpose:Final Project
//Date:5/3/24


#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000


typedef struct {
    int width;
    int height;
    char pixels[MAX_SIZE][MAX_SIZE];
} Image;


void load_image(Image *image);
void display_image(const Image *image);
void edit_image(Image *image);
void crop_image(Image *image);
void dim_image(Image *image);
void brighten_image(Image *image);
void save_image(const Image *image);
void rotate_image(Image *image);

int main() {
    Image current_image;
    char choice;

    while (true) {
        printf("\nMenu:\n");
        printf("1. Load a new image\n");
        printf("2. Display the current image\n");
        printf("3. Edit the current image\n");
        printf("4. Exit the program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                load_image(&current_image);
                break;
            case '2':
                display_image(&current_image);
                break;
            case '3':
                edit_image(&current_image);
                break;
            case '4':
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


void load_image(Image *image) {
    FILE *file = fopen("sampleimage.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    if (fscanf(file, "%d %d", &image->width, &image->height) != 2) {
        printf("Error reading image dimensions from file.\n");
        fclose(file);
        return;
    }

    
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            if (fscanf(file, " %c", &image->pixels[i][j]) != 1) {
                printf("Error reading image data from file.\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("Image loaded from file.\n");
}


void display_image(const Image *image) {
    printf("Displaying the current image...\n");
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            printf("%c", image->pixels[i][j]);
        }
        printf("\n");
    }
}


void edit_image(Image *image) {
    char choice;
    while (true) {
        printf("\nEdit Menu:\n");
        printf("1. Crop\n");
        printf("2. Dim\n");
        printf("3. Brighten\n");
        printf("4. Rotate 90 degrees\n");
        printf("5. Back to main menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                crop_image(image);
                break;
            case '2':
                dim_image(image);
                break;
            case '3':
                brighten_image(image);
                break;
            case '4':
                rotate_image(image);
            case '5':
                printf("Returning to main menu.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}


void crop_image(Image *image) {
    int x1, y1, x2, y2;
    printf("Enter top-left and bottom-right coordinates of the cropping rectangle: ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    
    if (x1 < 0 || x1 >= image->width || y1 < 0 || y1 >= image->height ||
        x2 < 0 || x2 >= image->width || y2 < 0 || y2 >= image->height ||
        x1 >= x2 || y1 >= y2) {
        printf("Invalid coordinates.\n");
        return;
    }

    printf("Cropping from (%d, %d) to (%d, %d)\n", x1, y1, x2, y2);

    
    int new_width = x2 - x1 + 1;
    int new_height = y2 - y1 + 1;

    printf("New width: %d, New height: %d\n", new_width, new_height);

    
    char cropped_pixels[MAX_SIZE][MAX_SIZE];

    
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            cropped_pixels[i][j] = image->pixels[y1 + i][x1 + j];
        }
    }

    
    image->width = new_width;
    image->height = new_height;

    
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            image->pixels[i][j] = cropped_pixels[i][j];
        }
    }

    printf("Image cropped successfully.\n");
    
  save_image(image);
}


void dim_image(Image *image) {
    printf("Dimming the image...\n");
    
    char brightness_levels[] = {' ', '.', 'o', 'O', '0'};
    
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            
            int current_brightness_index = 0;
            while (current_brightness_index < 5 && image->pixels[i][j] != brightness_levels[current_brightness_index]) {
                current_brightness_index++;
            }
            
            if (current_brightness_index > 0) {
                image->pixels[i][j] = brightness_levels[current_brightness_index - 1];
            }
        }
    }
 save_image(image);
}


void brighten_image(Image *image) {
    printf("Brightening the image...\n");
    
    char brightness_levels[] = {' ', '.', 'o', 'O', '0'};
    
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            
            int current_brightness_index = 0;
            while (current_brightness_index < 5 && image->pixels[i][j] != brightness_levels[current_brightness_index]) {
                current_brightness_index++;
            }
            
            if (current_brightness_index < 4) {
                image->pixels[i][j] = brightness_levels[current_brightness_index + 1];
            }
        }
    }
 save_image(image);
}
void save_image(const Image *image) {
    char response;
    printf("Do you want to save the edited image? (y/n): ");
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        char filename[100];
        printf("Enter the filename to save the image: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        
        fprintf(file, "%d %d\n", image->width, image->height);
        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fprintf(file, "%c", image->pixels[i][j]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
        printf("Image saved successfully as %s.\n", filename);
    }
}
void rotate_image(Image *image) {
    
    Image rotated_image;
    rotated_image.width = image->height;
    rotated_image.height = image->width;

    
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            rotated_image.pixels[j][image->height - 1 - i] = image->pixels[i][j];
        }
    }

    
    *image = rotated_image;

    printf("Image rotated 90 degrees clockwise.\n");
    
    save_image(image);
}
