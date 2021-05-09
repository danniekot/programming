#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fileencoding=utf-8
import discord
import os
import time
from discord.ext import commands
letters = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя '-."
go_to_game = ["cities", "города", "играть в города", "поиграем в города", "Давай в города"]
help_me = ["помощь", "помоги", "хелп", "help", "pomogi", "pomosh"]
is_game_starting = 0
client = discord.Client()
@client.event
async def on_ready():
    print('{0.user} has logged succesfull!'.format(client))
@client.event
async def on_message(message):
    global is_game_starting
    invalid_city = False
    if message.content.startswith('бот, привет'):
        await message.channel.send('Привет!')
    if is_game_starting == 1 and message.content in go_to_game:
        await message.channel.send('Игра уже начата!')
    elif is_game_starting == 0 and message.content in go_to_game:
        intro = open('D:\универ\Программирование\Kursovaja\console_intro.txt', 'r', encoding = 'utf-8')
        await message.channel.send(intro.read())
        is_game_starting = 1
        intro.close()
    if is_game_starting == 1 and message.author.id != client.user.id:
        if go_to_game.count(message.content) == 0 and help_me.count(message.content) == 0:
            for i in message.content:
                if letters.find(i) == -1:
                    await message.channel.send(f'Вы использовали запрещённый символ {i}!')
                    invalid_city = True
            if invalid_city == False:
                fin = open('D:\универ\Программирование\Kursovaja\console_user.txt', 'w')
                os.system(r'nul>fin')
                fin.write(message.content)
                fin.close()
                time.sleep(2)
                fout = open('D:\универ\Программирование\Kursovaja\console_bot.txt', 'r')
                fout_read = fout.read()
                if fout_read != "":
                    await message.channel.send(fout_read)
                    fout.close()
client.run('ODI5MDA1ODg4MzE1NzE5NzMx.YGx15Q.8jsbHSm3OTX9d_J8A1Tz9H8e1fY')
# команда для отладки: python D:\универ\Программирование\Kursovaja\Python\client.py
