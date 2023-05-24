#ifndef _WRITE_BLOCK_H
#define _WRITE_BLOCK_H

#include "Struct.h"
#include "Parameter.h"
#include "MarkovModelMatrix.h"
#include "SequenceSet.h"
#include "MotifSet.h"
#include "Motif.h"
#include "Pattern.h"
#include "Pwm.h"
#include "Global.h"

void print_params(FILE *fw1, Parameter parameter, SequenceSet sequences, MarkovModelMatrix markov);
void print_closure(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov);
void print_meme(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov);
void print_binding_sites(Parameter parameter, MotifSet motifs, SequenceSet sequences, MarkovModelMatrix markov);
 
#endif
