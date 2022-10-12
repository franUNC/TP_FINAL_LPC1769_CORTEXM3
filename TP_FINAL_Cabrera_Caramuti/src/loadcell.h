#ifndef LOADCELL_H_
#define LOADCELL_H_

uint16_t getWeight(void);
uint16_t getTare(uint16_t weight);
void start(uint16_t tare);
void stop(uint16_t* tare);

#endif /* LOADCELL_H_ */
