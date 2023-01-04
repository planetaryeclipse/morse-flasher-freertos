#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <stdio.h>

#include "pico/stdlib.h"

#define FLASH_LED_PIN 15
#define DOT_TICK_DELAY 20

#define MAX_READ_CHARS 100
#define MAX_QUEUED_FLASHES 400

static QueueHandle_t flash_queue = NULL;
static QueueHandle_t char_queue = NULL;

typedef enum
{
    DOT,
    DASH,
    INTRALETTER_SPACE,
    INTERLETTER_SPACE,
    INTERWORD_SPACE
} flash_type;

void flash_task(void *pvParameters)
{
    flash_type fval;

    while (1)
    {
        if (xQueueReceive(flash_queue, &fval, portMAX_DELAY) == pdTRUE)
        {
            // Flash received, will process and display

            if (fval == DOT)
            {
                // Flashes a dot
                gpio_put(FLASH_LED_PIN, 1);
                vTaskDelay(DOT_TICK_DELAY);
                gpio_put(FLASH_LED_PIN, 0);
            }
            else if (fval == DASH)
            {
                // Flashes a dash
                gpio_put(FLASH_LED_PIN, 1);
                vTaskDelay(DOT_TICK_DELAY * 3);
                gpio_put(FLASH_LED_PIN, 0);
            }
            else if (fval == INTRALETTER_SPACE){
                // Waits for length of a dot
                vTaskDelay(DOT_TICK_DELAY);
            } else if (fval == INTERLETTER_SPACE){
                // Waits for length of 3 dots
                vTaskDelay(DOT_TICK_DELAY * 3);
            } else if (fval == INTERWORD_SPACE){
                // Waits for length of 7 dots
                vTaskDelay(DOT_TICK_DELAY * 7);
            }
        }
    }
}

inline static void enqueue_flash(flash_type fval)
{
    xQueueSend(flash_queue, &fval, portMAX_DELAY);
}

void dequeueString()
{
    bool prev_char_was_ws = false;

    char c;
    while (uxQueueMessagesWaiting(char_queue) > 0)
    {
        xQueueReceive(char_queue, &c, portMAX_DELAY);

        printf("%c", c);

        // Ensures interletter spacing is present if 2 sequential non-whitespace characters are present
        if(c != ' ' && !prev_char_was_ws)
            enqueue_flash(INTERLETTER_SPACE);

        switch (c)
        {
        default:
            break;
        case 'a':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'b':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'c':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'd':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'e':
            enqueue_flash(DOT);
            break;
        case 'f':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'g':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'h':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'i':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'j':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'k':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'l':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'm':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'n':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'o':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'p':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'q':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 'r':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 's':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case 't':
            enqueue_flash(DASH);
            break;
        case 'u':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'v':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'w':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'x':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'y':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case 'z':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case '0':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '1':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '2':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '3':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '4':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '5':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case '6':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case '7':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case '8':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case '9':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            break;
        case ',':
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case '.':
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DOT);
            enqueue_flash(INTRALETTER_SPACE);
            enqueue_flash(DASH);
            break;
        case ' ':
            enqueue_flash(INTERWORD_SPACE);
            break;
        };

        prev_char_was_ws = c == ' ';

    }
    printf("\n");
}

void receive_serial_task(void *pvParameters)
{
    while (1)
    {
        int c = getchar_timeout_us(0);
        if (c != PICO_ERROR_TIMEOUT)
        {

            if (c == '\r' || c == '\n')
            {
                dequeueString();
            }
            else
            {
                xQueueSend(char_queue, &c, portMAX_DELAY);
            }
        }
    }
}

int main()
{
    stdio_init_all();

    // Pin handling flashes
    gpio_init(FLASH_LED_PIN);
    gpio_set_dir(FLASH_LED_PIN, true);

    // Creates a queue of flashes
    flash_queue = xQueueCreate(100, sizeof(flash_type));
    char_queue = xQueueCreate(100, sizeof(char));

    // Starts up the flashing and receive serial tasks
    xTaskCreate(flash_task, "Flash_Task", 256, NULL, 1, NULL);
    xTaskCreate(receive_serial_task, "Receive_Serial_Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1)
    {
    };

    return 0;
}