from tkinter import *
from tkinter import ttk
from tkinter import filedialog
import subprocess
import os

class CryptoUI:
    def __init__(self) -> None:
        self.entry = {}
        self.button = {}
        self.textbox = {}
        self.textScroll = {}
        self.label = {}
        pass
    

    def call_libC(self, arguments, name):
        # Path to your ELF file
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        elf_file_path = path + "/modules/" + name + "_call"

        # Arguments for your ELF file

        # Combine the file path and the arguments
        command = [elf_file_path] + arguments

        # Execute the command
        process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

        # Wait for the command to complete
        stdout, stderr = process.communicate()

        # Check if the process has encountered any errors
        if process.returncode != 0:
            return(f'Error: {stderr.decode()}')
        else:
            return(f'Result: \n{stdout.decode()}')

    def browseFiles0(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("all files",
                                                            "*.*"), ("Text files",
                                                            "*.txt*")))
        self.file0 = filename
        self.label[frame].configure(text= filename)
        
    def calculate_HashFile(self, frame):
        self.textbox[frame].insert(END, f'Input: {self.file0}\n')
        self.textbox[frame].insert(END, "md5sum: " + os.popen(f'md5sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "sha1sum: " + os.popen(f'sha1sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "sha256sum: " + os.popen(f'sha256sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "sha224sum: " + os.popen(f'sha224sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "sha384sum: " + os.popen(f'sha384sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "sha512sum: " + os.popen(f'sha512sum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, "CRC: " + os.popen(f'cksum "{self.file0}"').read().split()[0] + "\n")
        self.textbox[frame].insert(END, f'-------------------------------------\n')
        
        
    def build_HashFileFrame(self, frame): # frame for hash encryption
        self.file0 = ""

        mini_frame0 = Frame(frame, width=700, height=100)
        Label(mini_frame0, text="Input File").grid(row=0, column=0)
        self.label[frame] = Label(mini_frame0, text="Choose your file...", width=65)
        self.label[frame].grid(row=0, column=1)
        Button(mini_frame0, text="Explorer", command=lambda: self.browseFiles0(frame)).grid(row=0, column=2)
        Button(mini_frame0, text="HASH", command=lambda: self.calculate_HashFile(frame)).grid(row=1, column=1)
        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        self.textScroll[frame] = Scrollbar(mini_frame1, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame1, width=50, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)
        mini_frame1.grid()

    def calculate_Hash(self, frame, type):
        msg = self.entry[frame].get()
        self.textbox[frame].insert(END, f'Input: {msg}\n')
        self.textbox[frame].insert(END, self.call_libC([msg], type))
        self.textbox[frame].insert(END, f'-------------------------------------\n')


    def build_HashFrame(self, frame, type): # frame for hash encryption
        label = Label(frame, text="Input message").pack()
        self.entry[frame] = Entry(frame, width=50, borderwidth=5)
        self.entry[frame].pack()


        self.button[frame] = Button(frame, text="HASH", command=lambda: self.calculate_Hash(frame, type))
        self.button[frame].pack()

        self.textScroll[frame] = Scrollbar(frame)
        self.textScroll[frame].pack(side=RIGHT, fill=Y)

        self.textbox[frame] = Text(frame, width=52, height=30, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].pack()

        self.textScroll[frame].config(command=self.textbox[frame].yview)

    def setAESKey(self, v):
        self.AESkeyLength = v.get()
        #print(self.AESkeyLength)

    def setAESMode(self, v):
        self.AESmode = v.get()
        #print(self.AESkeyLength)
    def setAESaction(self, v):
        self.AESaction = v.get()
    def setAESinputType(self, v):
        self.AESinputType = v.get()


    def calculate_AES(self, frame):
        inputKey = self.entry[frame][0].get()
        inputMsg = self.entry[frame][1].get()
        iv = self.entry[frame][2].get()
        if iv == "":
            iv = "n/a"  
        keyLength = self.AESkeyLength
        mode = self.AESmode
        action = self.AESaction
        inputType = self.AESinputType

        #print(inputKey, inputMsg, iv, keyLength, mode, action, inputType)
        self.textbox[frame].insert(END, self.call_libC([inputKey, inputMsg, iv, keyLength, mode, action, inputType], "aes"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')


    def build_AESFrame(self, frame): #Frame for hash
        self.entry[frame] = [0, 0, 0]
        v = StringVar()
        inputType = [("Text", 0), ("Base64", 1)]
        keyValue = [("128", 0), ("192", 1), ("256", 2)]
        modes = [("ECB", 0), ("CBC", 1), ("CFB", 2)]
        actions = [("Encrypt", 0), ("Decrypt", 1)]
        
        mini_frame0 = Frame(frame, width=700, height=300)

        Label(mini_frame0, text="Input key").grid(row=0, column=0)
        self.entry[frame][0] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame][0].grid(row=0, column= 6)


        Label(mini_frame0, text="Key Length").grid(row=2,column= 0)
        self.AESkeyLength = "128"
        
        cnt = 2
        for i,j in keyValue:
            Radiobutton(mini_frame0, text=i, variable= v, command=lambda: self.setAESKey(v),
                   value=j).grid(row=2, column=cnt)
            cnt +=1 

        Label(mini_frame0, text="Mode").grid(row=3,column= 0)
        self.AESmode = "ECB"
        cnt = 2
        v2 = StringVar()
        for i,j in modes:
            Radiobutton(mini_frame0, text=i, variable= v2, command=lambda: self.setAESMode(v2),
                   value=j).grid(row=3, column=cnt)
            cnt +=1 
        
        Label(mini_frame0, text="Message/Cipher").grid(row=4, column=0)
        self.entry[frame][1] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame][1].grid(row=4, column= 6)

        Label(mini_frame0, text="Action").grid(row=5, column=0)
        self.AESaction = "Encrypt"
        cnt = 2
        v3 = StringVar()
        for i,j in actions:
            Radiobutton(mini_frame0, text=i, variable= v3, command=lambda: self.setAESaction(v3),
                   value=j).grid(row=5, column=cnt)
            cnt +=1 

        Label(mini_frame0, text="IV").grid(row=6, column=0)
        self.entry[frame][2] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame][2].grid(row=6, column= 6)


        Label(mini_frame0, text="Input type").grid(row=7, column=0)
        self.AESinputType = "Text"
        cnt = 2
        v4 = StringVar()
        for i,j in inputType:
            Radiobutton(mini_frame0, text=i, variable= v4, command=lambda: self.setAESinputType(v4),
                   value=j).grid(row=7, column=cnt)
            cnt +=1 

        self.button[frame] = Button(mini_frame0, text="Process", command=lambda: self.calculate_AES(frame))
        self.button[frame].grid(row=8, column=0)

        mini_frame0.grid()
        mini_frame1 = Frame(frame, width=700, height=100)

        self.textScroll[frame] = Scrollbar(mini_frame1, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame1, width=50, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)
        mini_frame1.grid()

    def browseFiles4(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file4 = filename
        self.label[frame][0].configure(text= filename)

    def browseFiles5(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file5 = filename
        self.label[frame][1].configure(text= filename)

    def calculate_RSAkeygen(self, frame):
        e = self.entry[frame][0].get()
        nb = self.entry[frame][1].get()
        mr = self.entry[frame][2].get()
        
        #print(nb, mr, e)
        self.textbox[frame].insert(END, self.call_libC([nb, mr, e], "rsa_keygen"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')
 
        return
    
    def calculate_RSAEnc(self, frame):
        msg = self.entry[frame][3].get()
        self.textbox[frame].insert(END, self.call_libC([self.file4, msg], "rsa_enc"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')
        return
    
    def calculate_RSADec(self, frame):
        cipher = self.entry[frame][4].get()
        self.textbox[frame].insert(END, self.call_libC([self.file5, cipher], "rsa_dec"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')
        return

    def build_RSAAlgoFrame(self, frame):
        self.entry[frame] = [x for x in range(7)]
        self.label[frame] = [x for x in range(7)]
        self.file4 = ""
        self.file5 = ""

        mini_frame0 = Frame(frame, width=700, height=100)

        Label(mini_frame0, text="e").grid(row=0, column=0)
        self.entry[frame][0] = Entry(mini_frame0, width=5, borderwidth=5)
        self.entry[frame][0].grid(row=0, column= 1)

        Label(mini_frame0, text="number of bits").grid(row=0, column=2)
        self.entry[frame][1] = Entry(mini_frame0, width=5, borderwidth=5)
        self.entry[frame][1].grid(row=0, column= 3)

        Label(mini_frame0, text="Miller-Rabin rounds").grid(row=0, column=4)
        self.entry[frame][2] = Entry(mini_frame0, width=5, borderwidth=5)
        self.entry[frame][2].grid(row=0, column= 5)

        Label(mini_frame0, text="\t\t     ").grid(row=0, column=6)
        self.button[frame] = Button(mini_frame0, text="Process keygen",borderwidth=5  ,command=lambda: self.calculate_RSAkeygen(frame))
        self.button[frame].grid(row=0, column=7)

        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        self.label[frame][0] = Label(mini_frame1, text="Choose public key file...", width=75)
        self.label[frame][0].grid(row=0, column=0)
        Button(mini_frame1, text="Explorer", borderwidth=5, command=lambda: self.browseFiles4(frame)).grid(row=0, column=1)

        self.label[frame][1] = Label(mini_frame1, text="Choose private key file...", width=75)
        self.label[frame][1].grid(row=1, column=0)
        Button(mini_frame1, text="Explorer", borderwidth=5, command=lambda: self.browseFiles5(frame)).grid(row=1, column=1)

        mini_frame1.grid()

        mini_frame2 = Frame(frame, width=700, height=100)
        
        #Label(mini_frame2, justify="left", text="Miller-Rabin rounds").grid(row=0, column=0)
        self.entry[frame][3] = Entry(mini_frame2, width=55, borderwidth=5)
        self.entry[frame][3].grid(row=1, column= 0)
        self.entry[frame][3].bind("<Button-1>", lambda e: self.entry[frame][3].delete(0, END))
        self.entry[frame][3].insert(0, "Enter a number to encrypt....")
        Button(mini_frame2, text="Encryption", borderwidth=5, command=lambda: self.calculate_RSAEnc(frame)).grid(row=1, column=2)

        self.entry[frame][4] = Entry(mini_frame2, width=55, borderwidth=5)
        self.entry[frame][4].grid(row=2, column= 0)
        self.entry[frame][4].bind("<Button-1>", lambda e: self.entry[frame][4].delete(0, END))
        self.entry[frame][4].insert(0, "Enter the encrypted number....")
        Label(mini_frame2, text="\t\t").grid(row=2, column=1)
        Button(mini_frame2, text="Decryption", borderwidth=5, command=lambda: self.calculate_RSADec(frame)).grid(row=2, column=2)

        mini_frame2.grid()

        mini_frame3 = Frame(frame, width=700, height=200)
        self.textScroll[frame] = Scrollbar(mini_frame3, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame3, width=55, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)

        mini_frame3.grid()
        return

    def browseFiles6(self, frame):
        path = os.path.dirname(os.path.realpath(__file__))
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file6 = filename
        self.label[frame][0].configure(text= filename)

    def browseFiles7(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file7 = filename
        self.label[frame][1].configure(text= filename)

    def calculate_RSASign(self, frame):
        msg = self.entry[frame][3].get()
        print(self.file6, msg)
        self.textbox[frame].insert(END, self.call_libC([self.file7, msg], "rsa_sign"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')

        return
    def calculate_RSAVerify(self, frame):
        msg = self.entry[frame][3].get()
        sign = self.entry[frame][4].get()

        self.textbox[frame].insert(END, self.call_libC([self.file6, msg, sign], "rsa_verify"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')

        return

    def build_RSASigFrame(self, frame):
        self.entry[frame] = [x for x in range(7)]
        self.label[frame] = [x for x in range(7)]

        mini_frame0 = Frame(frame, width=700, height=100)
        self.label[frame][0] = Label(mini_frame0, text="Choose public key file...", width=75)
        self.label[frame][0].grid(row=0, column=0)
        Button(mini_frame0, text="Explorer", borderwidth=5, command=lambda: self.browseFiles6(frame)).grid(row=0, column=1)

        self.label[frame][1] = Label(mini_frame0, text="Choose private key file...", width=75)
        self.label[frame][1].grid(row=1, column=0)
        Button(mini_frame0, text="Explorer", borderwidth=5, command=lambda: self.browseFiles7(frame)).grid(row=1, column=1)

        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        
        #Label(mini_frame2, justify="left", text="Miller-Rabin rounds").grid(row=0, column=0)
        self.entry[frame][3] = Entry(mini_frame1, width=55, borderwidth=5)
        self.entry[frame][3].grid(row=1, column= 0)
        self.entry[frame][3].bind("<Button-1>", lambda e: self.entry[frame][3].delete(0, END))
        self.entry[frame][3].insert(0, "Enter a message (as a number)...")
        Button(mini_frame1, text="Sign", borderwidth=5, command=lambda: self.calculate_RSASign(frame)).grid(row=1, column=2)

        self.entry[frame][4] = Entry(mini_frame1, width=55, borderwidth=5)
        self.entry[frame][4].grid(row=2, column= 0)
        self.entry[frame][4].bind("<Button-1>", lambda e: self.entry[frame][4].delete(0, END))
        self.entry[frame][4].insert(0, "Enter the signature...")
        Label(mini_frame1, text="\t\t").grid(row=2, column=1)
        Button(mini_frame1, text="Verify", borderwidth=5, command=lambda: self.calculate_RSAVerify(frame)).grid(row=2, column=2)

        mini_frame1.grid()

        mini_frame3 = Frame(frame, width=700, height=200)
        self.textScroll[frame] = Scrollbar(mini_frame3, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame3, width=55, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)

        mini_frame3.grid()

        return

    def setFactoringType(self, v):
        self.factoringType = v.get()
        return

    def calculate_factoring(self, frame):
        number = self.entry[frame].get()
        #print(self.factoringType, number)
        if self.factoringType == "0":
            self.textbox[frame].insert(END, self.call_libC([number], "fpr"))
            self.textbox[frame].insert(END, f'-------------------------------------\n')
        elif self.factoringType == "1":
            self.textbox[frame].insert(END, self.call_libC([number], "fecm"))
            self.textbox[frame].insert(END, f'-------------------------------------\n')
        else:
            self.textbox[frame].insert(END, self.call_libC([number], "ftd"))
            self.textbox[frame].insert(END, f'-------------------------------------\n')

    def build_FactoringFrame(self, frame):
        mini_frame0 = Frame(frame, width=700, height=100)

        Label(mini_frame0, text="Number\t\t").grid(row=0, column=0)
        self.entry[frame] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame].grid(row=0, column= 1)

        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        types = [("Pollard method rho (P)", "0"), ("ECM", "1"), ("Trial Division", "2")]
        cnt = 0
        v = StringVar()

        for i,j in types:
            Radiobutton(mini_frame1, text=i, variable= v, command=lambda: self.setFactoringType(v),
                   value=j).grid(row=0, column=cnt)
            cnt +=1 
        Button(mini_frame1, text="Factorize", borderwidth=5, command=lambda: self.calculate_factoring(frame)).grid(row=1, column=1)
        mini_frame1.grid()

        mini_frame3 = Frame(frame, width=700, height=200)
        self.textScroll[frame] = Scrollbar(mini_frame3, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame3, width=55, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)

        mini_frame3.grid()

        return

    def setCheckPrimeType(self, v):
        self.checkPrimeType = v.get()
        return

    def calculate_checkprime(self, frame):
        number = self.entry[frame][0].get()
        rounds = self.entry[frame][1].get()
        #print(self.checkPrimeType, number)

        if self.checkPrimeType == "0":
            self.textbox[frame].insert(END, self.call_libC([number, rounds], "prime_fermat"))
            self.textbox[frame].insert(END, f'-------------------------------------\n')
        elif self.checkPrimeType == "1":
            self.textbox[frame].insert(END, self.call_libC([number, rounds], "prime_millerrabin"))
            self.textbox[frame].insert(END, f'-------------------------------------\n')

    def build_CheckPrimeFrame(self, frame):
        self.entry[frame] = [0, 0]
        mini_frame0 = Frame(frame, width=700, height=100)

        Label(mini_frame0, text="Number\t\t").grid(row=0, column=0)
        self.entry[frame][0] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame][0].grid(row=0, column= 1)

        Label(mini_frame0, text="Rounds\t\t").grid(row=1, column=0)
        self.entry[frame][1] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame][1].grid(row=1, column= 1)

        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        types = [("Fermat", "0"), ("Millet Rabin", "1")]
        cnt = 0
        v = StringVar()

        for i,j in types:
            Radiobutton(mini_frame1, text=i, variable= v, command=lambda: self.setCheckPrimeType(v),
                   value=j).grid(row=0, column=cnt+2)
            cnt +=1 
        Button(mini_frame1, text="Factorize", borderwidth=5, command=lambda: self.calculate_checkprime(frame)).grid(row=1, column=1)
        mini_frame1.grid()

        mini_frame3 = Frame(frame, width=700, height=200)
        self.textScroll[frame] = Scrollbar(mini_frame3, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame3, width=55, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)

        mini_frame3.grid()
        return

    def setHLAinputType(self, v):
        self.hashtype = v.get()

    def calculate_HLA(self, frame):
        print(self.hashtype, self.entry[frame][0].get(), self.entry[frame][1].get())
        self.textbox[frame].insert(END, self.call_libC([self.hashtype, self.entry[frame][0].get(), self.entry[frame][1].get()], "hla"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')


    def build_HLAFrame(self, frame):
        self.entry[frame] = [0, 0]
        self.hashtype = 0

        hashType = [("md5", "0"), ("sha1", "1"), ("sha256", "2"), ("sha512", "3")]
        mini_frame0 = Frame(frame, width=700, height=100)
        Label(mini_frame0, text="Hex Digest").grid(row=0, column=0)
        self.entry[frame][0] = Entry(mini_frame0, width=60, borderwidth=5)
        self.entry[frame][0].grid(row=0, column= 2)

        Label(mini_frame0, text="Ext Message").grid(row=1, column=0)
        self.entry[frame][1] = Entry(mini_frame0, width=60, borderwidth=5)
        self.entry[frame][1].grid(row=1, column= 2)

        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        v = StringVar()
        cnt = 1
        for i,j in hashType:
            Radiobutton(mini_frame1, text=i, variable= v, command=lambda: self.setHLAinputType(v),
                   value=j).grid(row=0, column=cnt)
            cnt +=1 

        Button(mini_frame1, text="Attack", command=lambda: self.calculate_HLA(frame)).grid(row=1, column=0)
        mini_frame1.grid()

        mini_frame2 = Frame(frame, width=700, height=300)
        self.textScroll[frame] = Scrollbar(mini_frame2, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NSEW)

        self.textbox[frame] = Text(mini_frame2, width=55, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)
        mini_frame2.grid()


    def browseFiles1(self, frame):
        path = os.path.dirname(os.path.realpath(__file__))
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file1 = filename
        self.label[frame][0].configure(text= filename)
    
    def browseFiles2(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file2 = filename
        self.label[frame][1].configure(text= filename)

    def calculate_SquareAES1(self, frame):
        key = self.entry[frame].get()
        #print(key, self.file1)
        self.textbox[frame].insert(END, self.call_libC(["0", self.file1, key], "squareaes"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')

    def calculate_SquareAES2(self, frame):
        #print(self.file2)
        self.textbox[frame].insert(END, self.call_libC(["1", self.file2], "squareaes"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')

    def build_SquareFrame(self, frame):
        self.file1 = ""
        self.file2 = ""
        self.label[frame] = ["", ""]

        mini_frame0 = Frame(frame, width=700, height=100)
        Label(mini_frame0, text="Plaintext").grid(row=0, column=0)
        self.label[frame][0] = Label(mini_frame0, text="Choose your file...", width=65)
        self.label[frame][0].grid(row=0, column=1)
        Button(mini_frame0, text="Explorer", command=lambda: self.browseFiles1(frame)).grid(row=0, column=2)
        Label(mini_frame0, text="Key").grid(row=1, column=0)      
        self.entry[frame] = Entry(mini_frame0, width=40, borderwidth=5)
        self.entry[frame].grid(row=1, column= 1) 
        Button(mini_frame0, text="Encrypt List In File", command=lambda: self.calculate_SquareAES1(frame)).grid(row=2, column=1)

        Label(mini_frame0, text="Ciphertext").grid(row=4, column=0)
        self.label[frame][1] = Label(mini_frame0, text="Choose your file...", width=65)
        self.label[frame][1].grid(row=4, column=1)
        Button(mini_frame0, text="Explorer", command=lambda: self.browseFiles2(frame)).grid(row=4, column=2)
        
        Button(mini_frame0, text="Attack", command=lambda: self.calculate_SquareAES2(frame)).grid(row=5, column=1)
        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        self.textScroll[frame] = Scrollbar(mini_frame1, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame1, width=50, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)
        mini_frame1.grid()

    def browseFiles3(self, frame):
        #path = os.path.dirname(os.path.realpath(__file__))
        path = os.getcwd()
        filename = filedialog.askopenfilename(initialdir = path,
                                            title = "Select a File",
                                            filetypes = (("Text files",
                                                            "*.txt*"),
                                                        ("all files",
                                                            "*.*")))
        self.file3 = filename
        self.label[frame].configure(text= filename)

    def calculate_Md5Col(self, frame):
        #print(key, self.file3)
        self.textbox[frame].insert(END, self.call_libC([self.file3], "md5col"))
        self.textbox[frame].insert(END, f'-------------------------------------\n')

    def build_Md5ColFrame(self, frame):
        self.file3 = ""

        mini_frame0 = Frame(frame, width=700, height=100)
        Label(mini_frame0, text="Prefix File").grid(row=0, column=0)
        self.label[frame] = Label(mini_frame0, text="Choose your file...", width=65)
        self.label[frame].grid(row=0, column=1)
        Button(mini_frame0, text="Explorer", command=lambda: self.browseFiles3(frame)).grid(row=0, column=2)
        Button(mini_frame0, text="Attack", command=lambda: self.calculate_Md5Col(frame)).grid(row=1, column=0)
        mini_frame0.grid()

        mini_frame1 = Frame(frame, width=700, height=100)
        self.textScroll[frame] = Scrollbar(mini_frame1, orient=VERTICAL)
        self.textScroll[frame].grid(row=0,column=1,  sticky=NS)

        self.textbox[frame] = Text(mini_frame1, width=50, height=20, font=("Helvetica", 16), yscrollcommand=self.textScroll[frame].set)
        self.textbox[frame].grid(row=0, column=0)

        self.textScroll[frame].config(command=self.textbox[frame].yview)
        mini_frame1.grid()



    def build(self):
        #   root frame
        self.root = Tk()
        self.root.title('Crypto Calculator Group 14A')
        self.root.geometry("700x700")

        #   notebook 
        self.v_notebook = ttk.Notebook(self.root)
        self.v_notebook.pack(pady=15)


        # Hash tab
        self.hash_Frame = Frame(self.v_notebook)
        self.hash_Notebook = ttk.Notebook(self.hash_Frame)
        self.hash_Notebook.pack()

        self.v_frame1 = Frame(self.hash_Notebook , width=500, height=500)   # MD5 frame
        self.v_frame2 = Frame(self.hash_Notebook , width=500, height=500)   # SHA1 frame
        self.v_frame3 = Frame(self.hash_Notebook , width=500, height=500)   # SHA256, 224, 512, 384 frame
        self.v_frame3_1 = Frame(self.hash_Notebook , width=500, height=500) 
        self.v_frame3_2 = Frame(self.hash_Notebook , width=500, height=500) # File

        self.v_notebook.add(self.hash_Frame, text="Hash")
        self.hash_Notebook.add(self.v_frame1, text="MD5")
        self.hash_Notebook.add(self.v_frame2, text="SHA1")
        self.hash_Notebook.add(self.v_frame3, text="SHA2")
        self.hash_Notebook.add(self.v_frame3_1, text="CRC")
        self.hash_Notebook.add(self.v_frame3_2, text="File")

        #   Symetric tab
        self.symetric_Frame = Frame(self.v_notebook)
        self.symetric_Notebook = ttk.Notebook(self.symetric_Frame)
        self.symetric_Notebook.pack()

        self.v_frame4 = Frame(self.symetric_Notebook, width=700, height=700)   # AES frame

        self.v_notebook.add(self.symetric_Frame, text="Symetric")
        self.symetric_Notebook.add(self.v_frame4, text="AES")

        #   Asymmetric tab
        self.Asymetric_Frame = Frame(self.v_notebook)
        self.Asymetric_Notebook = ttk.Notebook(self.Asymetric_Frame)
        self.Asymetric_Notebook.pack()

        self.v_frame5 = Frame(self.Asymetric_Frame, width=700, height=700)   #  RSA Algorithm
        self.v_frame5_1 = Frame(self.Asymetric_Frame, width=700, height=700) #  RSA Signature
        self.v_frame5_2 = Frame(self.Asymetric_Frame, width=700, height=700) #  Factoring
        self.v_frame5_3= Frame(self.Asymetric_Frame, width=700, height=700)  #  Check Prime

        self.v_notebook.add(self.Asymetric_Frame, text="Asymetric")
        self.Asymetric_Notebook.add(self.v_frame5, text="RSA Algorithm")
        self.Asymetric_Notebook.add(self.v_frame5_1, text="RSA Signature")
        self.Asymetric_Notebook.add(self.v_frame5_2, text="Factoring")
        self.Asymetric_Notebook.add(self.v_frame5_3, text="Check Prime")

        #   Attack tab
        self.Attack_Frame = Frame(self.v_notebook)
        self.Attack_Notebook = ttk.Notebook(self.Attack_Frame)
        self.Attack_Notebook.pack()

        self.v_frame6 = Frame(self.Attack_Notebook, width=700, height=700)   # HashLength Attack frame
        self.v_frame7 = Frame(self.Attack_Notebook, width=700, height=700)   # SquareAES frame
        self.v_frame8 = Frame(self.Attack_Notebook, width=700, height=700)   #md5 col
        
        self.v_notebook.add(self.Attack_Frame, text="Attack")

        self.Attack_Notebook.add(self.v_frame6, text="Hash Length Attack")
        self.Attack_Notebook.add(self.v_frame7, text="Square AES")
        self.Attack_Notebook.add(self.v_frame8, text="MD5 Collison")

        #   Base convert

        #   build each frame
        self.build_HashFrame(self.v_frame1, "md5")
        self.build_HashFrame(self.v_frame2, "sha1")
        self.build_HashFrame(self.v_frame3, "sha2")
        self.build_HashFrame(self.v_frame3_1, "crc")
        self.build_HashFileFrame(self.v_frame3_2)


        self.build_AESFrame(self.v_frame4)

        self.build_RSAAlgoFrame(self.v_frame5)
        self.build_RSASigFrame(self.v_frame5_1)

        self.build_FactoringFrame(self.v_frame5_2)

        self.build_CheckPrimeFrame(self.v_frame5_3)

        self.build_HLAFrame(self.v_frame6)

        self.build_SquareFrame(self.v_frame7)

        self.build_Md5ColFrame(self.v_frame8)

        #   pack everything
        self.root.mainloop()

def main():
    ui = CryptoUI()
    ui.build()

if __name__ == "__main__":
    main()

