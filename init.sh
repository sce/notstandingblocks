#!/bin/bash

echo Touching AUTHORS, NEWS, README and ChangeLog, which are required by automake..

touch AUTHORS NEWS README ChangeLog \
&& echo Run ./boostrap to prep makefiles \(create Makefile.in\)
