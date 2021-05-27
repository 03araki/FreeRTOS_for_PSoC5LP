/* ========================================
 *
 * Copyright Nozomu Araki, University of Hyogo, 2021
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Nozomu Araki.
 *
 * ========================================
*/
#include "project.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <stdio.h>

#define TASK_STACK_LED  128
#define TASK_STACK_UART 1000
#define TASK_PRIORITY_LED   (tskIDLE_PRIORITY + 1)
#define TASK_PRIORITY_UART  (tskIDLE_PRIORITY + 1)

void Task_LED1(void *pvParameters);     // LED1 に対する処理
void Task_LED2(void *pvParameters);     // LED2 に対する処理
void Task_UART_RX(void *pvParameters);  // UART (受信) に対する処理
void Task_UART_TX(void *pvParameters);  // UART (送信) に対する処理

uint g_iTXFlag = 0;
uint g_iStackCheck = 0;

// FreeRTOS の初期化処理
void prvHardwereSetup(void) {
    extern void xPortPendSVHandler(void);
    extern void xPortSysTickHandler(void);
    extern void vPortSVCHandler(void);
    extern cyisraddress CyRamVectors[];
    CyRamVectors[11] = (cyisraddress) vPortSVCHandler;
    CyRamVectors[14] = (cyisraddress) xPortPendSVHandler;
    CyRamVectors[15] = (cyisraddress) xPortSysTickHandler;
}

// FreeRTOS のエラー処理
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    taskDISABLE_INTERRUPTS();
    for(;;);
}

// FreeRTOS のエラー処理
void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    for(;;);
}


int main(void)
{
    prvHardwereSetup();
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    
    // タスクの登録
    xTaskCreate(Task_LED1,
        "LED1",
        TASK_STACK_LED,
        NULL,
        1,
        NULL);
    xTaskCreate(Task_LED2,
        "LED2",
        TASK_STACK_LED,
        NULL,
        1,
        NULL);
    xTaskCreate(Task_UART_RX,
        "UART_RX",
        TASK_STACK_UART,
        NULL,
        1,
        NULL);
    xTaskCreate(Task_UART_TX,
        "UART_TX",
        TASK_STACK_UART,
        NULL,
        1,
        NULL);
        
    vTaskStartScheduler();  // Start RTOS Kernel

    for(;;)
    {
        /* Place your application code here. */
        
    }
}

void Task_LED1(void *pvParameters)
{
    const portTickType xDelay = 500 / portTICK_RATE_MS;
    
    while(1)
    {
        LED1_Write(~LED1_Read());

        vTaskDelay(xDelay);
    }
}

void Task_LED2(void *pvParameters)
{
    const portTickType xDelay = 100 / portTICK_RATE_MS;
    
    while(1)
    {
        LED2_Write(~LED2_Read());
        
        vTaskDelay(xDelay);
    }
}

void Task_UART_RX(void *pvParameters)
{
    char c;

    while(1) {
        c = UART_GetChar();
        switch(c) {
            case 'a':
            g_iTXFlag = !g_iTXFlag;
            break;
            case 'l':
            LED3_Write(~LED3_Read());
            break;
            case 't':
            if(g_iTXFlag) g_iTXFlag = 0;
            g_iStackCheck = 1;
            break;
        }
        taskYIELD();
    }
}

void Task_UART_TX(void *pvParameters) 
{
    char buf[512];
    const portTickType xDelay = 10 / portTICK_RATE_MS;
    
    while(1) {
        if(g_iTXFlag) {
            sprintf(buf, "LED1 = %d, LED2 = %d\r\n", LED1_Read(), LED2_Read());
            UART_PutString(buf);
        }
        else if(g_iStackCheck) {
            UART_PutString("************************************************\r\n");
            vTaskList(buf);     // スタックサイズの確認
            UART_PutString(buf);
            UART_PutString("************************************************\r\n");
            g_iStackCheck = 0;
        }
        
        vTaskDelay(xDelay);
    }
}
/* [] END OF FILE */
