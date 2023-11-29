# [START import_libraries]
import argparse
import base64
import httplib2
import logging

import picamera
import numpy as np
from gtts import gTTS
from subprocess import call
from time import sleep


from googleapiclient import discovery
from oauth2client.service_account import ServiceAccountCredentials
from httplib2 import Http

# The url template to retrieve the discovery document for trusted testers.
DISCOVERY_URL='https://{api}.googleapis.com/$discovery/rest?version={apiVersion}'
# [END import_libraries]


logging.basicConfig(level=logging.INFO)

# gTTs 음성안내 사용
def playTTS(label):
    """Play the label"""
    tts = gTTS(text=label, lang='en')   # lang='ko'
    tts.save('result.mp3')
    call(['mplayer', 'result.mp3'])


def main(photo_file):
    """Run a label request on a single image"""

    # [START authenticate]
#    credentials = GoogleCredentials.get_application_default()
    scopes = ['https://www.googleapis.com/auth/cloud-platform']
    credentials = ServiceAccountCredentials.from_json_keyfile_name(
    '/home/alisa/key.json', scopes)
    http_auth = credentials.authorize(Http())
    service = discovery.build('vision', 'v1', credentials=credentials,
                              discoveryServiceUrl=DISCOVERY_URL)

    # [END authenticate]

    # [START construct_request]
    with open(photo_file, 'rb') as image:
        image_content = base64.b64encode(image.read())
        service_request = service.images().annotate(body={
            'requests': [{
                'image': {
                    'content': image_content.decode('UTF-8')
                },
                'features': [{
                    'type': 'LABEL_DETECTION',
                    'maxResults': 10
                }]
            }]
        })
        # [END construct_request]
        # [START parse_response]
        response = service_request.execute()
        label = response['responses'][0]['labelAnnotations'][0]['description']
        print(response)
        
        # 음성안내 함수 호출
        playTTS(label)

        print('Found label: %s for %s' % (label, photo_file))
        return 0
        # [END parse_response]

# [START run_application]
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('image_file', help='The image you\'d like to label.')
    args = parser.parse_args()
    main(args.image_file)
# [END run_application]
