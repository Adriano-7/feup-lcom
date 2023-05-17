// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"

extern uint8_t output;
extern struct packet pp;

// Any header files included below this line should have been created by you
int main(int argc, char *argv[]){
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt){
  int ipc_status;
  message msg;

  uint8_t mouse_bit_no;

  // Configure the mouse
  if (mouse_enable_data_reporting()){
    printf("Error while enabling the mouse data report\n");
    return 1;
  }

  if (mouse_subscribe_interrupts(&mouse_bit_no)){
    printf("Error while subscribing the mouse interrupts\n");
    return 1;
  }

  while (cnt > 0){
    printf("cnt: %d\n", cnt);

    if (driver_receive(ANY, &msg, &ipc_status)){
      printf("driver_receive failed");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch (_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        if (msg.m_notify.interrupts & BIT(4)){
          printf("Mouse interrupt received\n");
          mouse_ih();

          printf("output: %x\n", output);

          if(mouse_parse_output()){
            printf("packet: received\n");
            
            mouse_build_packet();
            mouse_print_packet(&pp);
            cnt--;
          }
          
          else{
            printf("Still more packets to go\n");
          }

        }
      }
    }
  }

  printf("left the loop\n");

  // Reset the mouse configuration
  if (disable_data_report()){
    printf("Error while disabling the mouse data report\n");
    return 1;
  }

  if (mouse_unsubscribe_interrupts()){
    printf("Error while unsubscribing the mouse interrupts\n");
    return 1;
  }

  return 0;
}

int(mouse_test_async)(uint8_t idle_time){
  /* To be completed */
  printf("%s(%u): under construction\n", __func__, idle_time);
  return 1;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance){
  /* To be completed */
  printf("%s: under construction\n", __func__);
  return 1;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt){
  /* This year you need not implement this. */
  printf("%s(%u, %u): under construction\n", __func__, period, cnt);
  return 1;
}
