#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

class HsAgent;

typedef int (*HsMsgHandle)(HsAgent*, char*, int);

typedef struct {
	int msg_id;
	HsMsgHandle msg_handle;
} HsHandlePair;

typedef struct {
	const HsHandlePair* pairs;
	int npairs;
} HsNetServerConfig;

#endif
