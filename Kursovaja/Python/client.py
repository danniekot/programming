#!/usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fileencoding=utf-8
import discord
import os
from discord.ext import commands
letters = "АБВГДЕЁЖДИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя '-."
go_to_game = ["cities", "города", "играть в города", "поиграем в города", "Давай в города"]
is_game_starting = 0
client = discord.Client()
@client.event
async def on_ready():
    print('{0.user} has logged succesfull!'.format(client))
@client.event
async def on_message(message):
    global is_game_starting
    fout = open('D:\универ\Программирование\Kursovaja\console_bot.txt', 'r', encoding = 'utf-8')
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
        if go_to_game.count(message.content) == 0:
            for i in message.content:
                if letters.find(i) == -1:
                    await message.channel.send(f'Вы использовали запрещённый символ {i}!')
                    break
                else:
                    fin = open('D:\универ\Программирование\Kursovaja\console_user.txt', 'w')
                    os.system(r'nul>fin')
                    fin.write(message.content)
                    empty = ''
                    empty.encode('ascii', 'replace')
                    if fout.read() != empty:
                        await message.channel.send(fout.read())
                        break
client.run('ODI5MDA1ODg4MzE1NzE5NzMx.YGx15Q.WwcRONqGbwy3DFQTU-UCKktcIeI')
# команда для отладки: python D:\универ\Программирование\Kursovaja\Python\client.py
