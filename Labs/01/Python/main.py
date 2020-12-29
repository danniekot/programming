from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)

		desc.config(text=str(forecast_j["description"]))
		temp.config(text=str(round(forecast_j["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.geometry('200x270')
root.title("Погода")
root.bind("<Button-1>", reload_data)

yellow, white = "#e9c04d", "#ffffff"
w, h = 100, 30

top =    Frame(root, bg=yellow, width=w, height=h)
middle = Frame(root, bg=white,  width=w, height=h*3)
bottom = Frame(root, bg=yellow, width=w, height=h)

top.pack(side=TOP, fill=X)
middle.pack(expand=True, fill=BOTH)
bottom.pack(side=BOTTOM, fill=X)

city = Label(top, font=("Calibri Bold", 12), text="Симферополь", bg=yellow)
desc = Label(top, font=("Calibri", 12), bg=yellow)
temp = Label(middle, font=("Impact", 48), bg=white)

city.pack(pady=0)
desc.pack(pady=0)
temp.pack(expand=True)

reload_data()
root.mainloop()
