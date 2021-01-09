from tkinter import *
from PIL import ImageTk

root = Tk()
root.geometry('888x666')
root.configure(background="#444444")
root.title("Lines 98")
img = ImageTk.PhotoImage(file="cell.png")
for row in range(9):
    for col in range(9):
        lbl = Label(root, image=img, borderwidth=0)
        lbl.place(x=col*70+30, y=row*70+20)
root.mainloop()
