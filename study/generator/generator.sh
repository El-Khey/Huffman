#!/bin/bash

python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 1000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 5000 
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 10000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 100000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 500000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 1000000 
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 5000000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 10000000
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000



python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 2
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 4
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 8
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 16
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 32
python3 study/generator/text_file_generator.py --output_dir ./study/test/raw/ --size 50000000 --num_chars 64