#include <lcom/lcf.h>
#include "controllers/handleInterrupt.h"
#include "game.h"
#include "devices/keyboard.h"
#include "devices/timer.h"
#include "devices/vbe.h"
#include "devices/graphics.h"
#include "model/game/player.h"
#include "model/gameObject.h"

#include "assets/imgs/ivan.xpm"
#include "assets/imgs/osvaldo.xpm"
#include "assets/imgs/miro.xpm"
#include "assets/imgs/nave.xpm"

#include "state.h"

extern uint8_t output;

int game_loop(){
	//bool running = true;
	//enum State state = MENU;

	int ipc_status, r;
	message msg;

	//Keyboard
	bool secondByte = false;
	uint8_t bytes[2];
	uint8_t keyboard_bit_no;

	//Timer
	uint8_t timer_bit_no;

	//Player

	xpm_image_t img;
	uint8_t* img_colors;
	img_colors = xpm_load(nave_xpm,XPM_INDEXED,&img);
	GameObject* gameObject = createGameObject(0,0,3,img,img_colors,true);
	drawGameObject(gameObject);
	//Player* player = createPlayer();

	if(timer_subscribe_int(&timer_bit_no)){
	printf("Error while subscribing timer interrupt\n");
	return 1;
	}

	if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
	printf("Error subscribing keyboard interrupts\n");
	return 1;
	}

	/*
	if(map_phys_mem(0x105)){
	printf("Error mapping the physical to virtual memory"); 
	return 1;
	}

	if(set_graphics_mode(0x105)){
	printf("Error setting graphics mode\n");
	return 1;
	}
	*/

	//xpm_map_t xpm = monster1_xpm;
	//draw_xpm(osvaldo_xpm,50,50);
	//draw_xpm(ivan_xpm,50,150);
	//draw_xpm(miro_xpm,50,200);
	//draw_xpm(nave_xpm,200,800);



	//2nd Initialize game
	while(output != BREAK_ESC){
	if((r = driver_receive(ANY, &msg, &ipc_status))) {
		printf("driver_receive failed with: %d", r);
		continue;
	}

	if (is_ipc_notify(ipc_status)) {
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE:
			if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
			kbc_ih();
			if(secondByte){
				secondByte=false;
				bytes[1]=output;
				//handle_keyboard(state,bytes,player);
			}
			else{
				bytes[0] = output;
				if(output==0xE0){
				secondByte = true;
				}
				else{
					//handle_keyboard(state,bytes,player);
				}
			}


			}
			if (msg.m_notify.interrupts & BIT(timer_bit_no)){
			timer_int_handler();
			
			}
			break;
			}
		}
	} 


	//3rd Loop/Receive interrupts


	//4th Unsubscribe interrupts
	if(timer_unsubscribe_int()){
	printf("Error while unsubscribing timer interrupt\n");
	return 1;
	}

	if(keyboard_unsubscribe_interrupts()){
	printf("Error unsubscribing keyboard interrupts\n");
	return 1;
	}

	if(vg_exit()){
	printf("Error exiting graphics mode\n");
	return 1;
	}

	return 0;
}
