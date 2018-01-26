#! /usr/bin/python3

from urllib.request import urlopen
import json
import sys
import os

# Extract command line arguments and grab the wunderground API key
#location = sys.argv[1]
location = "Cluj-Napoca"
apiKey = open(os.getenv('HOME') + '/.api/wunderground', 'r').readline().split('\n')[0]

# Wunderground API call for current conditions data
f = urlopen('http://api.wunderground.com/api/' + apiKey + '/conditions/q/' + location + '.json')
json_string = f.read()
f.close()
parsed_json = json.loads(json_string)
current = parsed_json['current_observation']

# Print current data
temp = current['temp_c']
#flike = current['feelslike_c']
cond = current['weather']
print('{}°C | {}'.format(temp, cond))
