/*
 * mcp.h
 *
 * Created: 04.10.2016 15:06:28
 *  Author: nikolasn
 */ 


#ifndef MCP_H_
#define MCP_H_

//---FUNCTIONS---
void mcp_init();

char mcp_read(char address);

void mcp_write(char address, char data);

void mcp_requestSend();

char mcp_readStatus();

void mcp_bitModify(char address, char mask, char data);

void mcp_reset();

#endif /* MCP_H_ */