import sys
from concurrent.futures import ThreadPoolExecutor, as_completed
import requests


def req(url):
    r = requests.get(url,stream=True)
    return url + ' -  '+str(r.status_code)

processes = []

with open(sys.argv[2]) as file:
    f = file.readlines()
    f = [i.rstrip('\n') for i in f]

try:
    with ThreadPoolExecutor(max_workers=10) as executor:
        for i in f:
            processes.append(executor.submit(req,sys.argv[1]+'/'+str(i)))

except:
    print('An Error Occured During '+sys.argv[1]+'/'+str(i))

for task in as_completed(processes):
    print(task.result())
