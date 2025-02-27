/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TIMEOUT 100


#define LED_COUNT 19  // Change as needed
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint16_t Button_Pressed = RESET;
uint8_t buffer[5];
// i2c LM75B sensor code
static const uint8_t LSM6DSO_ADDR = 0xD4;  // I2C address of LSM6DSO









//I2C sensor
static const uint8_t LSM6DSO_REG_OUTX_L_XL = 0x28;  // X-axis acceleration data low byte
static const uint8_t LSM6DSO_REG_OUTX_H_XL = 0x29;  // X-axis acceleration data high byte
static const uint8_t LSM6DSO_REG_OUTY_L_XL = 0x2A;  // Y-axis acceleration data low byte
static const uint8_t LSM6DSO_REG_OUTY_H_XL = 0x2B;  // Y-axis acceleration data high byte
static const uint8_t LSM6DSO_REG_OUTZ_L_XL = 0x2C;  // Z-axis acceleration data low byte
static const uint8_t LSM6DSO_REG_OUTZ_H_XL = 0x2D;  // Z-axis acceleration data high byte

volatile int woke_up = 0; // Flag to track wake-up
volatile int sleep_flag = 0; // Start with Sleep mode enabled



// APA102 led SPI
uint8_t spiBuffer[4 + (LED_COUNT * 4) + 4]; // Start (4 bytes w 0x00) + LED Frames + End Frame (4 bytes w 0xFF) // LED frame is 4 bytes so you multiply led count by 4;
// start and stop is only needed for first and last transmit;

int red = 0;
int blue = 0;
int green = 0;
int brightness = 0;




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */







/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	// Optional: Send a message before entering Sleep mode
	char msg[] = "Entering Sleep mode...\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);


	float temp_c;
	HAL_StatusTypeDef ret;
	uint8_t buf[16];
	int16_t val;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */




  //static const uint8_t TOS_REG = 0x03;
  //static const uint8_t ctrl1_xl_value = 0x40;
  //static const uint8_t TOS_DATA_LSB = 0x00;
  //uint8_t dataBuffer[2]; // buffer for register address and data
  //dataBuffer[0] = LSM6DSO_REG_CTRL1_XL; // register address
  //dataBuffer[1] = ctrl1_xl_value; // 1st data byte

  //ret = HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, dataBuffer, sizeof(dataBuffer), TIMEOUT);
  //if ( ret != HAL_OK ) {
    //strcpy((char*)buf, "Er OS 1\r\n");
  //} else {
  	//strcpy((char*)buf, "TOS done\r\n");
    //}
  // Send out buffer (temperature or error message)
  //HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), TIMEOUT);




  // i2c TMP102 sensor code
  // Tell TMP102 that we want to read from the temperature register





    // For 500 mg (~0.5g), set WAKE_UP_THS = 16 (0x10), since 500 / 31.25 ≈ 16.
    // Threshold for wake-up: 1 LSB weight depends on WAKE_THS_W in WAKE_UP_DUR (5Ch);
    // WAKE_UP_DUR (5Ch) default value: 000000 = (0: 1 LSB = FS_XL / (26); = 64; 1 LSB weight 64;
    // FS_XL = +-2000mg -> 4000/64 = 31.25 mg;
    // for 1000mg treshhold: 1000mg / 31.25 = 32;





    void LSM6DSOTR_Init(void) {
        uint8_t data[2];

        // Full reset
        data[0] = 0x12; data[1] = 0x01; // CTRL3_C: SW_RESET
        ret = HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        if (ret != HAL_OK) printf("Reset failed\n");
        HAL_Delay(100);

        // Enable accelerometer, high-performance
        data[0] = 0x10; data[1] = 0x40; // CTRL1_XL: 104 Hz, ±2g
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);




        // registers for INT trigger wake up

        data[0] = 0x15; data[1] = 0x00; // CTRL6_C: XL_HM_MODE = 0
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // Enable high-pass filter
        data[0] = 0x17; data[1] = 0x00; // CTRL8_XL: HP_EN = 1
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // Set wake-up threshold to 31.25 mg
        data[0] = 0x5B; data[1] = 0x08;
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // Immediate wake-up
        data[0] = 0x5C; data[1] = 0x00; // WAKE_UP_DUR
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // Enable slope filter and interrupts
        data[0] = 0x56; data[1] = 0x00; // TAP_CFG0: SLOPE_FDS = 1
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // Route wake-up to INT1
        data[0] = 0x5E; data[1] = 0x20; // MD1_CFG: INT1_WU = 1
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);

        // INT1 push-pull, active-high
        data[0] = 0x12; data[1] = 0x44; // CTRL3_C
        HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, data, 2, 100);
        HAL_Delay(50);


/*
        // Verify all registers
        uint8_t vald;
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x0F, 1, &vald, 1, 100); printf("WHO_AM_I: 0x%02X\n", vald); // 0x6C
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x10, 1, &vald, 1, 100); printf("CTRL1_XL: 0x%02X\n", vald);  // 0x040
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x15, 1, &vald, 1, 100); printf("CTRL6_C: 0x%02X\n", vald); // 0x00
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x17, 1, &vald, 1, 100); printf("CTRL8_XL: 0x%02X\n", vald); // 0x10
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x56, 1, &vald, 1, 100); printf("TAP_CFG0: 0x%02X\n", vald); // 0x10
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x5B, 1, &vald, 1, 100); printf("WAKE_UP_THS: 0x%02X\n", vald); // 0x01
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x5E, 1, &vald, 1, 100); printf("MD1_CFG: 0x%02X\n", vald); // 0x20
        HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x12, 1, &vald, 1, 100); printf("CTRL3_C: 0x%02X\n", vald); // 0x40
*/
    }


    LSM6DSOTR_Init();




    // Send out buffer (temperature or error message)
    //HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), TIMEOUT);
    //HAL_Delay(1000);



    void setLEDColor(int index, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness) {
        if (index >= LED_COUNT) return;

        spiBuffer[4 + (index * 4)] = 0xE0 | (brightness & 0x1F); // Brightness (0-31); in datasheet there is 32 total brightness levels, 0 - 31; 5 bits;
        // brightness byte first 3 bits from MSB always need to be set 111 or 0XE0;

        // 0x1F = 0b00011111 → This masks only the lower 5 bits; bitwase AND operation - &; If both bits are 1, the result is 1; otherwise, the result is 0.
        // If brightness = 20 (0b00010100), → brightness & 0x1F = 0b00010100 (remains 20);
        // If brightness = 50 (0b00110010), → brightness & 0x1F = 0b00011111 (caps it at 31);
        // 50 = 0b00110010 & 0x1F = 0b00011111 = 0b00011111 (becomes 31 (maximum valid value));
        // Why Use & 0x1F; limits brightness to 5 bits (0-31); If the user inputs brightness = 100, the bitwise AND forces it back to 31.

        // 0xE0 | (brightness & 0x1F); This combines the fixed 0b11100000 with the brightness value.
        // If brightness = 20 (0b00010100): 0b11100000 | 0b00010100 = 0b11110100  // Equals 0xF4;
        // If brightness = 31 (0b00011111): 0b11100000 | 0b00011111 = 0b11111111  // Equals 0xFF;
        // If brightness = 0 (0b00000000): 0b11100000 | 0b00000000 = 0b11100000  // Equals 0xE0 (minimum brightness)
        spiBuffer[4 + (index * 4) + 1] = blue;
        spiBuffer[4 + (index * 4) + 2] = green;
        spiBuffer[4 + (index * 4) + 3] = red;
    }

    void updateAPA102() {
        // Send Start Frame (4 bytes of 0x00)
        memset(spiBuffer, 0x00, 4); // memset() is a standard C library function that sets a block of memory to a specific value;
        // Using memset() ensures that the first 4 bytes of spiBuffer are correctly set to 0x00.
        // Equivalent Manual Code (Without memset): spiBuffer[0] = 0x00; spiBuffer[1] = 0x00; spiBuffer[2] = 0x00; spiBuffer[3] = 0x00;
        // Here, spiBuffer is already a pointer to the first element of the array.
        // In C, when you use an array name without an index (spiBuffer), it automatically decays into a pointer to its first element (&spiBuffer[0]).
        // So, spiBuffer is equivalent to &spiBuffer[0];

        // End Frame (must be at least LED_COUNT / 2 bits set to 1)
        memset(&spiBuffer[4 + (LED_COUNT * 4)], 0xFF, 4);
        // The & (address-of operator) is used to pass the memory address of a specific position inside spiBuffer.
        // &spiBuffer[4 + (LED_COUNT * 4)] → Pointer to the position in spiBuffer where the End Frame starts.
        // 0xFF → The value we want to fill (11111111 in binary). 4 → Number of bytes to set.

        // This is incorrect because spiBuffer[4 + (LED_COUNT * 4)] is a single uint8_t value, not a pointer.
        // memset() expects a pointer, but without &, we are passing an integer value, which causes an error.
        // Here, spiBuffer[4 + (LED_COUNT * 4)] refers to a specific element in the array.
        // However, we don’t want to pass the value of that element (which is a single uint8_t).
        // Instead, we need to pass the memory address of that element.
        // Using & gives us the pointer to that specific position, which memset() requires.

        // Golden Rule: If passing the entire array, don’t use &. If passing a specific element’s address, use &.

        HAL_SPI_Transmit(&hspi1, spiBuffer, sizeof(spiBuffer), TIMEOUT);
    }

    void setLEDStrip() {
        for (int i = 0; i < LED_COUNT; i++) {
            setLEDColor(i, red, green, blue, brightness); // Red color, max brightness
        }
        updateAPA102();
    }

    //void enter_sleep(void)
    //{
      //HAL_SuspendTick();
      //HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
      // After waking up, resume SysTick, continues where it left off, after wake up and trigger EXTU_callback executes;
      //HAL_ResumeTick();
    //}

    //enter_sleep(); // Sleep initially


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // without any low power improvements 28 ma consumption;





	  // The MCU knows PA0 is the wake-up trigger because:
	  // MX_GPIO_Init configures PA0 as an EXTI input on Line 0.
	  // The EXTI0 interrupt is enabled and mapped to PA0 in hardware.
	  // HAL_GPIO_EXTI_Callback confirms PA0 triggered it with GPIO_PIN_0.






	  //Use a flag to decide when to sleep, so the MCU only enters Sleep mode when you explicitly want it to. For example:
	  if (sleep_flag)
	      {
	       HAL_SuspendTick();
	       HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	   	   //After waking up, resume SysTick, continues where it left off, after wake up and trigger EXTU_callback executes;
	       HAL_ResumeTick();
	      }



	    // Suspend SysTick to prevent it from waking the CPU every 1 ms
	    //HAL_SuspendTick();

	    // Enter Sleep mode using WFI (Wait For Interrupt)
	    //HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);



	    // After the ISR completes, the program returns to the exact point where it entered
	    // Sleep mode—right after the HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI) call in your while (1) loop.

	    // Here’s how it plays out with your example:
	    // The MCU enters Sleep mode at HAL_PWR_EnterSLEEPMode.
	    // PA0 triggers an EXTI interrupt, waking the MCU.
	    // HAL_GPIO_EXTI_Callback executes (e.g., you could toggle an LED here).
	    // Control returns to the while (1) loop, executing HAL_ResumeTick() and the UART message transmission.


	    // HAL_ResumeTick() re-enables the SysTick interrupt, but it’s only needed for the HAL timekeeping functions
	    // (e.g., HAL_Delay or HAL_GetTick) to work correctly in the main loop after wake-up.
	    //It’s not required for the CPU to process the EXTI interrupt itself.


	    // After waking up, resume SysTick
	    //HAL_ResumeTick(); // Resumes here after ISR



	    // This runs AFTER the callback
//	    if (woke_up)
//	       {
//	         char msg[] = "Woke up via PA0!\r\n";
//	         HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);
//	         woke_up = 0; // Reset flag
//	       }




	  uint8_t wake_up_src, accel_data[6];
	  // Read all axes
	  HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x28, 1, accel_data, 6, 100); // OUTX_L_XL to OUTZ_H_XL
	  int16_t accel_x = (int16_t)(accel_data[1] << 8 | accel_data[0]);
	  int16_t accel_y = (int16_t)(accel_data[3] << 8 | accel_data[2]);
	  int16_t accel_z = (int16_t)(accel_data[5] << 8 | accel_data[4]);
	  HAL_I2C_Mem_Read(&hi2c1, LSM6DSO_ADDR, 0x1B, 1, &wake_up_src, 1, 100);
	  uint8_t int1_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);

	  printf("WAKE_UP_SRC: 0x%02X, X: %d, Y: %d, Z: %d, INT1: %d\n", wake_up_src, accel_x, accel_y, accel_z, int1_state);
	    if (wake_up_src & 0x08) {
	       val = 0xFF;
	          }
	  HAL_Delay(100);




/*
	  // i2c TMP102 sensor code
	  // Tell TMP102 that we want to read from the temperature register
	    //buf[0] = LSM6DSO_REG_OUTX_L_XL; //x axis
	    buf[0] = LSM6DSO_REG_OUTY_L_XL; // y axis
	    //buf[0] = LSM6DSO_REG_OUTZ_L_XL; // z axis // when not moving and staying horizontal z reads arround 1g bc gravity;
	    ret = HAL_I2C_Master_Transmit(&hi2c1, LSM6DSO_ADDR, buf, 1, TIMEOUT);
	    if ( ret != HAL_OK ) {
	      strcpy((char*)buf, "Error Tx\r\n");
	    } else {
	      // Read 2 bytes from the temperature register
	      ret = HAL_I2C_Master_Receive(&hi2c1, LSM6DSO_ADDR, buf, 2, TIMEOUT); // | 0x01 read address ends w 1;
	      if ( ret != HAL_OK ) {
	        strcpy((char*)buf, "Error Rx\r\n");
	      } else {
	        //Combine the bytes
	        val = ((int16_t)buf[1] << 8) | (buf[0]);
	        // Convert to 2's complement, since temperature can be negative
	        //if ( val > 0x7FFF ) { //checks if the value is greater than 0x7FF, which in binary is 0111 1111 1111, if exceeded then its negative number;
	          //val |= 0xF000; // performs a bitwise OR with 0xF000 (which is 1111 0000 0000 0000 in binary).
	          // This operation sets the upper 4 bits of val to 1, effectively extending the sign bit from the 12th position to the 16th position.
	        //} // When using int16_t in C, no extra conversion is needed—just combine MSB and LSB correctly.
	        //temp_c = val * 1.0;
	        //sprintf((char*)buf, "value X: %u\r\n", (unsigned int)val);
	        printf("Sensor Value: %d\n", val);
	        // Understanding the 16-bit Output Range: The total number of possible values (steps) is 65,5; 2^16;
	        // he LSM6DSO accelerometer in ±2g mode means it can measure from -2g to 2g = 4000mg;
	        // 4000mg / 65536 = 0.061 mg/LSB;
	        // val = -565 (in dec) * 0.061 = -34.465 mg / 1000 = - 0.0345 g
	      }
	    }
	    // Send out buffer (temperature or error message)
	    //HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), TIMEOUT);
*/

	    brightness = 10;

	    if (val >= 16000 || val <= -16000){
	    	red = 255;
	    	blue = 0;
	    	green = 0;
		    setLEDStrip();
	    } else if (val <= 15999 && val >= 1000){
	    	red = 0;
	    	blue = 255;
	    	green = 0;
	    	setLEDStrip();
	    } else if (val <= -1000 && val >= -15999){
	    	red = 0;
	    	blue = 0;
	    	green = 255;
	    	setLEDStrip();
	    } else if (val <= 999 && val >= -999){
	    	red = 255;
	    	blue = 255;
	    	green = 255;
	    	setLEDStrip();
	    }


	    HAL_Delay(100);


	    //if (sleep_flag)
	    //{
	    //enter_sleep(); // Go back to sleep after work is done
	    //}
	    //sleep_flag = 1; // go back to sleep in next loop start

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000608;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_11, GPIO_PIN_SET);

  /*Configure GPIO pins : PA4 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{



	// In Sleep mode (WFI), the CPU wakes up for any enabled interrupt, including any configured EXTI line.
	//The MCU doesn’t care which one wakes it—it just resumes execution and lets the NVIC sort it out.

	// Each pin (PA0, PB1, PC2) is tied to a unique EXTI line (EXTI0, EXTI1, EXTI2);


	if (GPIO_Pin == GPIO_PIN_8) // PA0 (EXTI0) // Check if PA0 triggered the interrupt
	  {
		// Do something when PA0 wakes the MCU

		// This runs FIRST on wake-up
		sleep_flag = 0;
		woke_up = 1; // Set flag for main loop; this make sure that the wake up was from GPIO_PIN_0 not some other pin;
		// if its other pin trigger then you can put else statement to go back to sleep;
		// Optional: Add immediate actions here (e.g., toggle LED)

	    // Code here runs after wake-up (e.g., toggle an LED or log event)
		// This runs FIRST after wake-up
		// e.g., toggle an LED or set a flag

	  }
//	else // Any other trigger pin that woke mcu up (e.g., PB1, PC2, etc.)
//	{
	// Go back to Sleep mode immediately
//	HAL_SuspendTick(); // Suspend SysTick to avoid unwanted wake-ups
//	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);

	// The HAL_ResumeTick() after the Sleep call only runs if another interrupt wakes it again.
//	HAL_ResumeTick(); // This runs after waking up again

//	}


	//switch(GPIO_Pin)
	//{
	//case GPIO_PIN_13: // u cant make EXTI same pin on  other port so no need for port specification
	//	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14, GPIO_PIN_SET); // on
	//	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_7 | GPIO_PIN_14);
	//	break;
	//default:
	//	break;
	//}
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	HAL_UART_Receive_IT(&huart1, buffer, 5);
//	HAL_UART_Transmit(&huart1, buffer, 5, 0xFFFF); //interrupt callback isn’t reached until you enter 5 characters.
	//At that point, the 5 characters are transmitted from the device
//}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
