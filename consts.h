const int IN_MEM_HMERGE_READY_UNIT = 1 << 20; // cache size , in byte
const int IN_MEM_HMERGE_LENGTH = 100; //  
const int IN_MEM_VMERGE_LENGTH = 100; // stream write
const int IN_MEM_VMERGE_READY_UNIT = 0; // stream read 

/*test needed*/
const int RECORD_SIZE = 50;
const int RECORD_SIZE_LARGE = 1000;
const int RECORD_NUM = 1 << 20;
const int RECORD_NUM_LARGE = 12 << 20;
const int RECORD_NUM_JOMBO = 120 << 20;