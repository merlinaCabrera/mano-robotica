/*
 * MEF.C
 */

#ifndef _MEF_H_
#define _MEF_H_

typedef enum {START, CONNECTING, FAIL, WAITING, CONTROLLING, SUCCESS1} states;

void MEF_init(void);
void MEF_update(void);


#endif
