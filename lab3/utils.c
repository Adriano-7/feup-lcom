#include <lcom/lcf.h>

#include <stdint.h>

extern uint8_t cnt;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL) return 1;

  *lsb = (uint8_t) val & 0x00FF;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL) return 1;

  *msb = (uint8_t) (val >> 8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value==NULL) return 1;

  uint32_t v2;
  if(sys_inb(port, &v2)){
      printf("Error reading from port %d\n", port);
      return 1;
  }
  *value = (uint8_t) v2;
  
  #ifdef LAB3
  cnt++;
  #endif

  return 0;
}