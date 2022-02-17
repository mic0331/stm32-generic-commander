// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

int _read(int file, char *result, size_t len) {
    HAL_StatusTypeDef status;
    int retcode = 0;

    if (len != 0) {
        status = HAL_UART_Receive( &huart2, (uint8_t *) result, len, HAL_MAX_DELAY);

        if (status == HAL_OK) {
            retcode = len;
        } else {
            retcode = -1;
        }
    }
    return( retcode);
}

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 100);
	return len;
}

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{

	uint8_t i = 0;
	char ch;

	ch = getchar();
	while ( ( EOF != ch ) && ( i < bufferLength ) )
	{
		buffer[i] = (uint8_t) ch;
		i++;
		ch = getchar();
	}
	*readLength = i;

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSend(const uint8_t *buffer, const uint32_t bufferLength, uint32_t *sentLength)
{
	printf("%s",(char*)buffer);
	*sentLength = bufferLength;
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	printf("%s", buffer);
	return CONSOLE_SUCCESS;
}

