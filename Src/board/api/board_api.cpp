#include "board_api.hpp"
#include "cmsis_os.h"
#include "main.h"


void board_api::sleep_ms(uint32_t milliseconds)
{
  osDelay(milliseconds);
}

void board_api::Led::on()
{
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
}

void board_api::Led::off()
{
  HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
}
