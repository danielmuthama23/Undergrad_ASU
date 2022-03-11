# !/bin/bash

echo "Enter email address: "

read email_address

gpg --fingerprint ${email_address}

echo "Continue? (y/N)"

read cont

if [ "$cont" = "y" ]; then
    echo "Sign key on GUI (click publish)"

    gpg --output ~/Desktop/gpg_exports/${email_address}_signed.gpg --export --armor ${email_address}

    echo "Export saved as ${email_address}.gpg"
else
    echo "Key not signed"
fi
