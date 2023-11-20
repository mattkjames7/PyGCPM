from setuptools import setup, find_packages
from setuptools.command.install import install
import os
import platform
from setuptools.command.build_py import build_py
import subprocess


class CustomBuild(build_py):
    def run(self):
        self.execute(self.target_build, ())
        build_py.run(self)

    def target_build(self):
        if platform.system() == 'Windows':
            cwd = os.getcwd()
            os.chdir('PyGCPM/__data/libgcpm/')
            subprocess.check_call(['cmd','/c','compile.bat'])
            os.chdir(cwd)
        else:
            subprocess.check_call(['make', '-C', 'PyGCPM/__data/libgcpm'])



with open("README.md", "r") as fh:
    long_description = fh.read()

def getversion():
	'''
	read the version string from __init__
	
	'''
	#get the init file path
	thispath = os.path.abspath(os.path.dirname(__file__))+'/'
	initfile = thispath + 'PyGCPM/__init__.py'
	
	#read the file in
	f = open(initfile,'r')
	lines = f.readlines()
	f.close()
	
	#search for the version
	version = 'unknown'
	for l in lines:
		if '__version__' in l:
			s = l.split('=')
			version = s[-1].strip().strip('"').strip("'")
			break
	return version
	
version = getversion()

setup(
    name="PyGCPM",
    version=version,
    author="Matthew Knight James",
    author_email="mattkjames7@gmail.com",
    description="Python wrapper for the Global Core Plasma Model",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/mattkjames7/PyGCPM",
    packages=find_packages(),
    package_data={'testmodule2': ['**/*']},
    cmdclass={'build_py': CustomBuild},  
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GNU General Public License (GPL)",
        "Operating System :: POSIX",
    ],
    install_requires=[
		'numpy',
		'DateTimeTools>=0.0.6',
		'matplotlib',
	],
	include_package_data=True,
)



