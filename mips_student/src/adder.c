#include <stdio.h>
#include <mips.h>

void full_adder(Signal in1, Signal in2, Signal carry_in, Signal *out1, Signal *carry_out)
{
    Signal xor12, and12, cand;
    xor_circuit(in1, in2, &xor12);
    and_gate(in1, in2, &and12);
    and_gate(carry_in, xor12, &cand);
    xor_circuit(carry_in, xor12, out1);
    or_gate(cand, and12, carry_out);
}

void rca(Word in1, Word in2, Signal carry_in, Word *out1, Signal *carry_out)
{
    int i;
    Signal innercarry;
    innercarry = carry_in;
    for(i = 0; i < 32; i++){
      full_adder(in1.bit[i], in2.bit[i], innercarry, &out1->bit[i], &innercarry);
    }
    *carry_out = innercarry;
}

void test_full_adder()
{
    Signal a, b, c, out1, outc;
    for(a = 0; a <= 1; ++a){
      for(b = 0; b <= 1; ++b){
        for(c = 0; c <= 1; ++c){
          full_adder(a, b, c, &out1, &outc);
          printf("FA(%d, %d, %d) => %d, %d\n", a, b, c, out1, outc);
        }
      }
    }
}

void test_rca(int val1, int val2)
{
    Signal cout;
    Word w1, w2, out;
    word_set_value(&w1, val1);
    word_set_value(&w2, val2);
    rca(w1, w2, 0, &out, &cout);
    printf("%d + %d = %d (carry out: %d)\n", word_get_value(w1), word_get_value(w2), word_get_value(out), cout);
}
