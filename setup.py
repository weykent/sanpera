from setuptools import setup
from setuptools.dist import Distribution

# Do this first, so setuptools installs cffi immediately before trying to do
# the below import
Distribution(dict(setup_requires='cffi'))

from sanpera._api import ffi

setup(
    name='sanpera',
    version='0.2pre',
    description='Image manipulation library, powered by ImageMagick',
    author='Eevee',
    author_email='eevee.sanpera@veekun.com',
    url='http://eevee.github.com/sanpera/',
    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: ISC License (ISCL)',
        'Programming Language :: Python',
        'Topic :: Multimedia :: Graphics',
        'Topic :: Multimedia :: Graphics :: Graphics Conversion',
        'Topic :: Software Development :: Libraries',
    ],

    packages=['sanpera'],
    package_data={
        'sanpera': ['_api.c', '_api.h'],
    },
    install_requires=[
        'cffi',
    ],

    ext_modules=[ffi.verifier.get_extension()],
)
