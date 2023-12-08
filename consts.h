/* HARDWARE */

const int MEM_SIZE = 100 * (1 << 20);   // 100MB memory, also file unit size
const int FILE_SIZE = MEM_SIZE;
const int CACHE_SIZE = 1 << 20;

/* SIZE */
const int IN_MEM_HMERGE_UNIT_SIZE = CACHE_SIZE; // size per qsort
const int IN_MEM_HMERGE_LENGTH = MEM_SIZE / IN_MEM_HMERGE_UNIT_SIZE;
const int IN_MEM_VMERGE_LENGTH = 100; // max number of streams for a merge sort

/*test needed*/
const int ROW_SIZE = 50;
const int ROW_SIZE_LARGE = 1000;
const int ROW_NUM = 1 << 20;
const int ROW_NUM_LARGE = 12 << 20;
const int ROW_NUM_JOMBO = 120 << 20;

/* file name */
const char FLIE_PREFIX[] = "diskFile";
const int MAX_FILE_NAME_LENGTH = 32;
const int NUM_ROW_PER_FILE = FILE_SIZE / ROW_SIZE;
