#ifndef SENSOR_H
#define SENSOR_H

extern int sensor_value;

void sensor_init(void);
void sensor_task(void *pvParameters);
int sensor_read(void);

#endif