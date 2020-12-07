#define BLOCK_SIZE 4096 // 1 bloc sur disque = 4096 octets

typedef struct {
	FILE* file; // identification du fichier
	char mode; // lecture 'r' ou �criture 'w'
	unsigned char record[BLOCK_SIZE]; // tampon pour lire ou �criture
	int record_length; // nombre d'�l�ments dans le tampon
	int i_record; // indice dans le tampon
	char octet[8]; // pour expension d'un octet en 8 caract�res
	int i_octet; // indice dans octet
	int nb_octets; // nombre d'octets lus ou �crits
} Bin_file;