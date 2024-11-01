#!/bin/bash

TELEGRAM_BOT_TOKEN="7390421222:AAGip9xAZi4ofxNLqCK_jSUFatueJESYcUQ"
TELEGRAM_USER_ID="289405819"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TIME=60

if [ $CI_JOB_STATUS == "success" ]
    then
        STATUS="✅"
    elif [  $CI_JOB_STATUS  ==  "failed"  ]
    then
        STATUS="⛔"
fi




#All CI
if [ $CI_JOB_STATUS == "success" ] &&  [  $CI_JOB_STAGE   ==   "unit-test"   ]
    then
        STATUS="✅✅✅"
        TEXT="Stage: $CI_JOB_STAGE%0AStatus: $CI_JOB_STATUS ✅%0ACI complete: $CI_JOB_STATUS $STATUS%0AProject:+$CI_PROJECT_NAME%0AThe CI is completed. To complete the CD , click on the link and run DEPLOY%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
        curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
#deploy
elif [ $CI_JOB_STATUS == "success" ] &&  [  $CI_JOB_STAGE   ==   "deploy"   ]
    then
        STATUS="✅"
        TEXT="Stage: $CI_JOB_STAGE%0AStatus: $CI_JOB_STATUS $STATUS%0ACD complete: $CI_JOB_STATUS $STATUS%0AWe have deployed a new version on production%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
        curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null

else
    TEXT="Stage: $CI_JOB_STAGE%0AStatus: $CI_JOB_STATUS $STATUS%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
    curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
fi

