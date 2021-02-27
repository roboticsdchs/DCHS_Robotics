from setuptools import find_packages, setup
setup(
    name=’drive_and_sens’,
    packages=find_packages(include=['drive_pkg', 'sens_pkg']),
    version=’0.0.1',
    description=’car drive and sensor library to make working with pyFirmata easy for beginners’,
    install_requires=['pyfirmata']
)
