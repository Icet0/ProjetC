#define BLOCK_SIZE 4096 // 1 bloc sur disque = 4096 octets

typedef struct {
	FILE* file; // identification du fichier
	char mode; // lecture 'r' ou écriture 'w'
	unsigned char record[BLOCK_SIZE]; // tampon pour lire ou écriture
	int record_length; // nombre d'éléments dans le tampon
	int i_record; // indice dans le tampon
	char octet[8]; // pour expension d'un octet en 8 caractères
	int i_octet; // indice dans octet
	int nb_octets; // nombre d'octets lus ou écrits
} Bin_file;

Bin_file* open_bin_file(char*, char);
void write_bin_file(Bin_file*, char);
char read_bin_file(Bin_file*);
int close_bin_file(Bin_file*);



void TEST_GESTION_FICHIER();