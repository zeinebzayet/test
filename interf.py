from tkinter import *
import os

def client():
   os.system("../tube_nomme/client")
   os.system("../tube_nomme/client >>liste.txt")
  

def sel():
   if v.get()=="Tube":
      os.system("../tube_nomme/server")
      gui2 = Toplevel(gui)
      gui2.geometry("350x350")
      btn = Button(gui2, text ="Lancer un Client",command=client)
      btn.pack()
      gui2.mainloop()
          

gui = Tk()
gui.geometry("350x350")
label = Label(gui, text="Bienvenue ! Veuillez cocher votre choix",font= ('Helvetica 12 bold')).place(relx=.5, rely=.3,anchor= CENTER)


v = StringVar()
v.set(None) # initialiser

r1 = Radiobutton(gui, text=" Tube Nommé", variable=v, value="Tube", command=sel).place(anchor=CENTER, relx=.5, rely=.4)
#r1.pack(anchor = CENTER,fill=Y, ipady=120)

r2 = Radiobutton(gui, text=" Sockets : TCP", variable=v, value="Sockets", command=sel).place(anchor=CENTER, relx=.5, rely=.5)
#r2.pack(anchor = CENTER,fill=Y, ipady=10)

label = Label(gui)
label.pack()
gui.mainloop()