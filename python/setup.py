from setuptools import setup
from codecs import open
import os

here = os.path.abspath(os.path.dirname(__file__))

with open(os.path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

setup(
	name = 'CURandRTC',
	version = '0.1.7',
	description = 'Random number generation module based on ThrustRTC',
	long_description=long_description,
	long_description_content_type='text/markdown',  
	url='https://github.com/fynv/CURandRTC',
	license='Anti 996',
	author='Fei Yang',
	author_email='hyangfeih@gmail.com',
	keywords='GPU CUDA Random XORWOR',
	packages=['CURandRTC'],
	package_data = { 'CURandRTC': ['*.dll', '*.so']},
	install_requires = ['ThrustRTC']
)

