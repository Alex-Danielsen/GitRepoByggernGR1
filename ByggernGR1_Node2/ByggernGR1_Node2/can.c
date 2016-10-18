/*
 * can.c
 *
 * Created: 04.10.2016 16:26:48
 *  Author: nikolasn
 */ 

#include "can.h"
#include "mcp.h"
#include "MCP2515_macros.h"
#include <stdio.h>
#include <avr/delay.h>

void can_init(){
	 mcp_init();
	 volatile uint8_t canStat = mcp_read(MCP_CANSTAT);	 
	 
	 //turn off rollover mode
	 mcp_bitModify(MCP_RXB0CTRL, MCP_ROLLOVER_OFF,0x04);
	 //set interrupts to fire
	 mcp_bitModify(MCP_CANINTE,0x01,0xFF );
	 
	//Set to loopback mode - should be done in CAN driver
	//Input descriptions: ADress of register, mask (first 3 bits), mode
	mcp_bitModify(MCP_CANCTRL, MODE_MASK ,MODE_NORMAL);
	
	canStat = mcp_read(MCP_CANSTAT);
	if((canStat &MODE_MASK) == MODE_NORMAL){
		printf("Is in loopback mode - %i\n",canStat);
	}
	
}



void can_send(can_message *message){
	uint8_t len = message->length & 0x0F;
	
	mcp_write(MCP_TXB0SIDL, 0x00);
	mcp_write(MCP_TXB0SIDH, 0x01);
	mcp_write(MCP_TXB0DLC, len);
	
	for(uint8_t i = 0; i < len; i++){
		mcp_write(MCP_TXB0D0+i, message->data[i]);
	}
	
	
	mcp_requestSend(1);
}

can_message can_recieve(){
	can_message message;
	
	volatile uint8_t canIntf = mcp_read(MCP_CANINTF);	 
	
	if(mcp_read(MCP_CANSTAT) & 0x0C){
		message.id = mcp_read(MCP_RXB0SIDH)<<8 | mcp_read(MCP_RXB0SIDL);
		message.length = mcp_read(MCP_RXB0DLC) & 0x0F;
		for(uint8_t i = 0; i < message.length; i++){
			message.data[i] = mcp_read(MCP_RXB0D0 + i);
		}
	}else{
		printf("No new message\n");
	}
	
	//on the MCP_CANINTF register, set bit 0 to value 0. E.g. mask 0B00000001, value 0
	mcp_bitModify(MCP_CANINTF, 1, 0);
	
	return message;
}

