#include <stdint.h>
void JoystickInit(void);
void Timer2A_Init(uint32_t sampleRate);

//Places values into user request variables
uint16_t getJX(void);
uint16_t getJY(void);

/* Out-of-file variables */
//uint8_t sampleReady
