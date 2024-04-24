from collections import Counter

import numpy as np
import matplotlib.pyplot as plt
import json
import os

PLOTS_FOLDER = "study/plots/"

class CharacterAnalyzer:
    def __init__(self, text_file):
        self.text_file = text_file
        self.char_counts = None
        self.sorted_chars = None
        self.chars = None
        self.frequencies = None

    def analyze(self):
        """
        Analyze the character distribution in the text file.
        """
        with open(self.text_file, 'r') as file:
            text = file.read()

        # Count character frequencies
        self.char_counts = Counter(text)

        # Sort characters by frequency
        self.sorted_chars = sorted(self.char_counts.items(), key=lambda x: x[1], reverse=True)

        # Extract characters and frequencies
        self.chars = [char[0] for char in self.sorted_chars]
        self.frequencies = [char[1] for char in self.sorted_chars]
       
    def set_text_file(self, text_file):
        """
        Set the text file to analyze.
        """
        self.text_file = text_file
        
    def print_stats(self):
        """
        Print statistical data.
        """
        total_chars = sum(self.frequencies)
        unique_chars = len(self.chars)
        most_common_char, most_common_freq = self.sorted_chars[0]
        
        mean_freq = np.mean(self.frequencies)
        median_freq = np.median(self.frequencies)
        std_dev = np.std(self.frequencies)

        print(f"Total characters: {total_chars}")
        print(f"Unique characters: {unique_chars}")
        print(f"Ratio unique/total: {unique_chars/total_chars:.2f}")
        print(f"Most common character: '{most_common_char}' with frequency {most_common_freq}")
        print(f"Mean frequency: {mean_freq}")
        print(f"Median frequency: {median_freq}")
        print(f"Standard deviation: {std_dev}")
        
    def save_stats(self):
        """
        Save statistical data to a JSON file.
        """
        total_chars = sum(self.frequencies)
        unique_chars = len(self.chars)
        most_common_char, most_common_freq = self.sorted_chars[0]
        
        mean_freq = np.mean(self.frequencies)
        median_freq = np.median(self.frequencies)
        std_dev = np.std(self.frequencies)

        stats = {
            "total_chars": total_chars,
            "unique_chars": unique_chars,
            "most_common_char": most_common_char,
            "most_common_freq": most_common_freq,
            "mean_freq": round(mean_freq, 2),
            "median_freq": round(median_freq, 2),
            "std_dev": round(std_dev, 2)
        }
        
        dir_path = os.path.dirname(self.text_file)
        os.makedirs(os.path.join(dir_path, "stats/"), exist_ok=True)
        file_path = os.path.join(dir_path, "stats/", f"{self.text_file.split('/')[-1].split('.txt')[0]}_stats.json")
        
        with open(f"{file_path}_stats.json", 'w') as file:
            json.dump(stats, file, indent=4)
        
    def plot_character_distribution(self):
        """
        Plot character distribution curve.
        """
        plt.figure(figsize=(10, 6))
        plt.plot(self.chars, self.frequencies, marker='o', linestyle='-')
        plt.title("Character Distribution in Text File")
        plt.xlabel("Character")
        plt.ylabel("Frequency")
        plt.xticks(rotation=90)
        filename = self.text_file.split("/")[-1].split(".txt")[0]
        plt.savefig(f"{PLOTS_FOLDER}/{filename}_char_distribution.png")