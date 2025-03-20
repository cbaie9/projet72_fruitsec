#!/bin/bash

# 🛠️ Met à jour le système
echo "🔄 Mise à jour du système..."
sudo apt update && sudo apt upgrade -y

# 👤 Création de l'utilisateur "cb9" avec permissions root
echo "👤 Création de l'utilisateur cb9..."
sudo useradd -m -s /bin/bash cb9
echo "cb9:sin" | sudo chpasswd
sudo usermod -aG sudo cb9
echo "✅ Utilisateur cb9 créé avec les permissions root."

# 🖥️ Installation de VSCode
echo "🖥️ Installation de VSCode..."
wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor | sudo tee /usr/share/keyrings/packages.microsoft.gpg > /dev/null
echo "deb [arch=arm64 signed-by=/usr/share/keyrings/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" | sudo tee /etc/apt/sources.list.d/vscode.list
sudo apt update && sudo apt install code -y

# 🔌 Installation d'Arduino IDE
echo "🔌 Installation d'Arduino IDE..."
sudo apt install arduino -y

# 🟢 Installation de Node.js
echo "🟢 Installation de Node.js..."
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo bash -
sudo apt install -y nodejs

# 🔴 Installation de Node-RED
echo "🔴 Installation de Node-RED..."
sudo apt install -y npm
sudo npm install -g --unsafe-perm node-red

# 📂 Installation et configuration de vsftpd
echo "📂 Installation et configuration de vsftpd..."
sudo apt install -y vsftpd

# 🔧 Modifier la configuration de vsftpd
sudo tee /etc/vsftpd.conf > /dev/null <<EOL
listen=YES
listen_ipv6=NO
anonymous_enable=NO
local_enable=YES
write_enable=YES
local_root=/
chroot_local_user=NO
allow_writeable_chroot=YES
pasv_enable=YES
pasv_min_port=40000
pasv_max_port=50000
EOL

# 🛠️ Redémarrer vsftpd
echo "🔄 Redémarrage de vsftpd..."
sudo systemctl restart vsftpd
sudo systemctl enable vsftpd

# 🔑 Activer SSH
echo "🔑 Activation de SSH..."
sudo systemctl enable ssh
sudo systemctl start ssh

# ✅ Installation terminée
echo "✅ Installation et configuration terminées ! SSH est activé."
