import argparse
import numpy as np
import os

from character_analyzer import CharacterAnalyzer
import scipy.stats as stats

class TextFileGenerator(CharacterAnalyzer):
    def __init__(self, output_dir="test", size=10000):
        super().__init__(None)
        self.output_dir = output_dir
        self.size = size
        self.start_char = 32  # ASCII code for space
        self.end_char = 126 # ASCII code for ~

    def generate_text(self, frequencies):
        text = ""
        for char, freq in frequencies.items():
            text += char * int(self.size * freq) 
        return text

    def save_text_to_file(self, text, filename):
        with open(filename, 'w') as file:
            file.write(text)

    def generate_and_save_text(self, frequencies, filename):
        text = self.generate_text(frequencies)
        self.save_text_to_file(text, filename)
        
        self.set_text_file(filename)
        self.analyze()
        self.save_stats()
        self.plot_character_distribution()

    def linear_frequencies(self):
        num_chars = self.end_char - self.start_char + 1
        total_frequency = sum(range(1, num_chars + 1))  # Somme des nombres de 1 à num_chars
        frequencies = {}
        for i, char in enumerate(range(self.start_char, self.end_char + 1)):
            frequencies[chr(char)] = (i + 1) / total_frequency
        return frequencies

    def uniform_frequencies(self):
        num_chars = self.end_char - self.start_char + 1
        frequency = 1 / num_chars
        frequencies = {chr(char): frequency for char in range(self.start_char, self.end_char + 1)}
        return frequencies

    def normal_frequencies(self, mean, std_dev):
        num_chars = self.end_char - self.start_char + 1
        x = np.linspace(0, 1, num_chars)
        pdf = stats.norm.pdf(x, mean, std_dev)
        pdf /= pdf.sum()  # Normalize to sum to 1
        frequencies = {chr(char): pdf[i] for i, char in enumerate(range(self.start_char, self.end_char + 1))}
        return frequencies
    
    def zipf_frequencies(self, alpha):
        num_chars = self.end_char - self.start_char + 1
        x = np.linspace(1, num_chars, num_chars)
        pdf = 1 / x**alpha
        pdf /= pdf.sum()
        frequencies = {chr(char): pdf[i] for i, char in enumerate(range(self.start_char, self.end_char + 1))}
        return frequencies
    
    def random_frequencies(self):
        frequencies = {chr(char): np.random.rand() for char in range(self.start_char, self.end_char + 1)}
        frequencies = {char: freq / sum(frequencies.values()) for char, freq in frequencies.items()}
        return frequencies

    def generate_text_files(self):
        os.makedirs(self.output_dir, exist_ok=True)

        self.generate_and_save_text(self.linear_frequencies(), os.path.join(self.output_dir + "linear/", f"linear_" + str(self.size) + ".txt"))
        self.generate_and_save_text(self.uniform_frequencies(), os.path.join(self.output_dir + "uniform/", "uniform_" + str(self.size) + ".txt"))
        self.generate_and_save_text(self.normal_frequencies(0.5, 0.1), os.path.join(self.output_dir + "normal/", "normal_" + str(self.size) + ".txt"))
        self.generate_and_save_text(self.zipf_frequencies(1.5), os.path.join(self.output_dir + "zipf/", "zipf_" + str(self.size) + ".txt"))
        self.generate_and_save_text(self.random_frequencies(), os.path.join(self.output_dir + "random/", "random_" + str(self.size) + ".txt"))

        print(f"> Text files of size {self.size} generated in {self.output_dir}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate text files with different frequency distributions for testing Huffman compression.")
    parser.add_argument("--output_dir", type=str, default="test_files", help="Output directory for text files (default: 'test_files')")
    parser.add_argument("--size", type=int, default=10000, help="Length of the generated text (default: 10000)")
    args = parser.parse_args()

    generator = TextFileGenerator(output_dir=args.output_dir, size=args.size)
    generator.generate_text_files()
