
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<regex.h>

static int get_user_ids(int *serial_num, int *user_ids, int *num_id) {
    int status = 0;
    char *path = "/data/system/users/userlist.xml";
    FILE *fp;
    char line[1024];
    int num;
    int id_num = 0;
    char *pattern_nextSerialNumber = "nextSerialNumber=\"[0-9]+\"";
    char *pattern_userid = "id=\"[0-9]+\"";
    char *pattern_num = "[0-9]+";
    char nbuf[4] = {0};
    regex_t reg_serial_num;
    regex_t reg_user_id;
    regex_t reg_num;
    regmatch_t reg_match;
    char match[64] = {0};
    long len;
    int rc;
    int found_serial_num = 0;
    int found_user_id = 0;

    if (!serial_num || !user_ids || !num_id) {
        LOGE("error, invalid input\n");
        return -1;
    }

    fp = fopen(path, "r");
    if (!fp) {
        LOGE("error, it is fail to fopen.\n");
        return -1;
    }
    // complie for serial number.
    if (regcomp(&reg_serial_num, pattern_nextSerialNumber, REG_EXTENDED) < 0) {
        LOGE("error, regcomp for num\n");
        status = -1;
        goto out;
    }
    // complie for user id.
    if (regcomp(&reg_user_id, pattern_userid, REG_EXTENDED) < 0) {
        LOGE("error, regcomp for pattern_userid\n");
        status = -1;
        goto out;
    }
    // complie for number.
    if (regcomp(&reg_num, pattern_num, REG_EXTENDED) < 0) {
        LOGE("error, regcomp for pattern_userid\n");
        status = -1;
        goto out;
    }

    while (fgets(line, sizeof(line), fp)) {
        found_serial_num = 0;
        found_user_id = 0;
        // check line content.
        if (!regexec(&reg_serial_num, line, 1, &reg_match, 0)) {
            found_serial_num = 1;
        } else if (!regexec(&reg_user_id, line, 1, &reg_match, 0)) {
            found_user_id = 1;
        }
        // no found serial number and user id.
        if (found_serial_num == 0 && found_user_id == 0) {
             continue;
        }

        // get length of match.
        len = reg_match.rm_eo - reg_match.rm_so;
        if (len) {
            // get match data.
            memset(match, 0, sizeof(match));
            memcpy((void *)match, (const void *)(line + reg_match.rm_so), (size_t)len);
             // check number string.
	    rc = regexec(&reg_num, match, 1, &reg_match, 0);
	    if (rc == REG_NOMATCH) {
	        continue;
	    }
            // get length of number.
            len = reg_match.rm_eo - reg_match.rm_so;
            if (!len)
                continue;

            // convert to int
            memset(nbuf, 0, sizeof(nbuf));
            memcpy((void *)nbuf, (const void *)(match + reg_match.rm_so), (size_t)len);
            num = atoi(nbuf);

            // get serial number.
            if (found_serial_num)
                *serial_num = num;
            // get user id.
            if (found_user_id)
                if (id_num < *num_id)
                    user_ids[id_num++] = num;
        }
    }

    *num_id = id_num;

    status = 0;

out:
    fclose(fp);
    return status;
}

static int get_invaild_user_ids(char *out, int *num) {
    int serial_num;
    int ids[16] = {0};
    int ids_num = 16;
    int user_cnt = 0;
    int index_num, index_id;

    if (!out) {
        LOGE("error, invalid input.\n");
        return -1;
    }

    if (get_user_ids(&serial_num, ids, &ids_num)) {
        LOGE("error, failed to get user ids.\n");
        return -1;
    }

    // get invalid user id from 10.
    for (index_num = 10; index_num < serial_num; index_num++) {
        for (index_id = 0; index_id < ids_num; index_id++) {
            if (index_num == ids[index_id])
                break;
        }
        // no found, had been removed.
        if (index_id >= ids_num) {
            if (user_cnt < *num)
                out[user_cnt++] = (char)index_num;
        }
    }

    *num = user_cnt;

    return 0;
}
