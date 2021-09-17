#!/bin/bash
ls -l | grep "^......x..." | awk '{print $9}'
