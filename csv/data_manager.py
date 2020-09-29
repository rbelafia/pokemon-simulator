import csv
import os
import shutil
import wget

ID_LANGUAGE = '5'
ID_GEN = '18'
ID_VERSION = '23'
ID_LAST_VERSION = '29'

# https://github.com/veekun/pokedex/tree/master/pokedex/data/csv
file_names = ['move_names.csv', 'move_flavor_text.csv', 'moves.csv',
              'pokemon_species_names.csv', 'pokemon_species_flavor_text.csv',
              'pokemon_types.csv', 'pokemon.csv', 'pokemon_stats.csv',
              'pokemon_moves.csv', 'type_efficacy.csv']

os.mkdir('.tmp')
for name in file_names:
    url = 'https://raw.githubusercontent.com/veekun/pokedex/master/pokedex/data/csv/'
    wget.download(url + name, '.tmp/.' + name)


#########################
# Create the moves file #
#########################

moves = {}
# Names
with open('.tmp/.' + file_names[0]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row['local_language_id'] == ID_LANGUAGE and int(row['move_id']) < 10000:
            moves[int(row['move_id'])] = [row['name']]

# Description
with open('.tmp/.' + file_names[1]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row['language_id'] == ID_LANGUAGE and row['version_group_id'] == ID_GEN:
            moves[int(row['move_id'])].append(row['flavor_text'].replace("\n", " ").replace(";", " "))

# Category - Type - Power - Accuracy - PP - Priority
with open('.tmp/.' + file_names[2]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if int(row['id']) < 10000:
            moves[int(row['id'])].append(row['damage_class_id'])
            moves[int(row['id'])].append(row['type_id'])
            moves[int(row['id'])].append(row['power'])
            moves[int(row['id'])].append(row['accuracy'])
            moves[int(row['id'])].append(row['pp'])
            moves[int(row['id'])].append(row['priority'])

# Write the csv file
with open('moves_compact.csv', 'w') as file:
    writer = csv.writer(file, delimiter=';')
    writer.writerow(["id", "name", "description", "category", "type", "power", "accuracy", "pp", "priority"])

    for key, value in moves.items():
        row = [key]
        for val in value:
            row.append(val)
        writer.writerow(row)

###########################
# Create the pokemon file #
###########################

pokemons = {}
# Names
with open('.tmp/.' + file_names[3]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row['local_language_id'] == ID_LANGUAGE and int(row['pokemon_species_id']) < 10000:
            pokemons[int(row['pokemon_species_id'])] = [row['name']]

# Descriptions
with open('.tmp/.' + file_names[4]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if len(pokemons[int(row['species_id'])]) == 1:
            if row['version_id'] == ID_VERSION and row['language_id'] == ID_LANGUAGE:
                pokemons[int(row['species_id'])].append(row['flavor_text'].replace("\n", " ").replace(";", " "))
            elif row['version_id'] == ID_LAST_VERSION and row['language_id'] == ID_LANGUAGE:
                pokemons[int(row['species_id'])].append(row['flavor_text'].replace("\n", " ").replace(";", " "))

# Types
for value in pokemons.values():
    value.append('')
    value.append('')
with open('.tmp/.' + file_names[5]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if int(row['pokemon_id']) < 10000:
            pokemons[int(row['pokemon_id'])][int(row['slot']) + 1] = row['type_id']

# Height - Weight - Base experience
with open('.tmp/.' + file_names[6]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row['is_default'] == '1':
            pokemons[int(row['id'])].append(row['height'])
            pokemons[int(row['id'])].append(row['weight'])
            pokemons[int(row['id'])].append(row['base_experience'])

# Stats
with open('.tmp/.' + file_names[7]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if int(row['pokemon_id']) < 10000:
            pokemons[int(row['pokemon_id'])].append(row['base_stat'])

# Write the file
with open('pokemons_compact.csv', 'w') as file:
    writer = csv.writer(file,  delimiter=';')
    writer.writerow(["id", "name", "description", "type1", "type2", "height", "weight", "base_experience", "PV",
                     "attack", "defense", "spe.attack", "spe.def", 'speed'])

    for key, value in pokemons.items():
        row = [key]
        for val in value:
            row.append(val)
        writer.writerow(row)

##############################
# Create the move pool files #
##############################

pokemon_moves = {}
for key in pokemons.keys():
    pokemon_moves[key] = []

# Compute move pool for each pokemon
with open('.tmp/.' + file_names[8]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if row['version_group_id'] == ID_GEN and int(row['pokemon_id']) < 10000:
            pokemon_moves[int(row['pokemon_id'])].append(row['move_id'])

# Create files
for key, value in pokemons.items():
    index = str(key) if key > 99 else ('0' + str(key) if key > 9 else '00' + str(key))

    with open('moves/' + index + '-' + value[0] + '.csv', 'w') as file:
        writer = csv.writer(file,  delimiter=';')
        writer.writerow(["move_id", "move_name"])

        for val in pokemon_moves[key]:
            writer.writerow([val, moves[int(val)][0]])

#########################
# Create the type table #
#########################

types = []
for i in range(19):
    types.append([])
    for j in range(19):
        types[i].append(100)

with open('.tmp/.' + file_names[9]) as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        if int(row['damage_type_id']) < 10000:
            types[int(row['damage_type_id'])][int(row['target_type_id'])] = int(row['damage_factor'])

with open('types_compact.csv', 'w') as file:
    writer = csv.writer(file,  delimiter=';')

    for line in types:
        writer.writerow(line)

shutil.rmtree('.tmp')