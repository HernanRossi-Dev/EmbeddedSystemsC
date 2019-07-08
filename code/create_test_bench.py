import random

OUT_LEN = 20;
#symbols: [ T, V, W, X, Y, Z ]
#probabilities: [ 0.33, 0.30, 0.2, 0.1, 0.05, 0.02]
#bit combimation: [0, 10, 110, 1110, 11110, 11111]
#code length: [1, 2, 3, 4, 5, 5]

def main():
    encoded_output = open("test_bench.txt", "w+")
    symbols_output = open("test_bench_symbols.txt", "w+")
    for x in range(0, OUT_LEN):
        current_prob = random.random()
        if current_prob <= 0.02:
            encoded_output.write('11111')
            symbols_output.write('Z')
        elif current_prob <= 0.07:
            encoded_output.write('11110')
            symbols_output.write('Y')
        elif current_prob <= 0.17:
            encoded_output.write('1110')
            symbols_output.write('X')
        elif current_prob <= 0.37:
            encoded_output.write('110')
            symbols_output.write('W')
        elif current_prob <= 0.67:
            encoded_output.write('10')
            symbols_output.write('V')
        else:
            encoded_output.write('0')
            symbols_output.write('T')
    # encoded_output.write("\n" + str(OUT_LEN))
    encoded_output.close()
    symbols_output.close()
main()
