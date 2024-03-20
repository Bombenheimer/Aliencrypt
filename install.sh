#!/bin/bash

echo "Installing Aliencrypt..."

pyinstaller --onefile --clean --noconfirm --log-level=ERROR Aliencrypt.py

mv dist/Aliencrypt /usr/local/bin

rm -rf build/ dist/

shred -ufz -n 3 Aliencrypt.spec
