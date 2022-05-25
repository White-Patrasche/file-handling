#include "student.h"

#include <memory.h>
#include <stdio.h>  // 필요한 header file 추가 가능
#include <stdlib.h>
#include <string.h>

// 함수 readRecord()는 학생 레코드 파일에서 주어진 rrn에 해당하는 레코드를
// 읽어서 recordbuf에 저장하고, 이후 unpack() 함수를 호출하여 학생 타입의 변수에
// 레코드의 각 필드값을 저장한다. 성공하면 1을 그렇지 않으면 0을 리턴한다.
int readRecord(FILE *fp, STUDENT *s, int rrn);
// unpack() 함수는 recordbuf에 저장되어 있는 record에서 각 field를 추출하는 일을
// 한다.
void unpack(const char *recordbuf, STUDENT *s);

// 함수 writeRecord()는 학생 레코드 파일에 주어진 rrn에 해당하는 위치에
// recordbuf에 저장되어 있는 레코드를 저장한다. 이전에 pack() 함수를 호출하여
// recordbuf에 데이터를 채워 넣는다. 성공적으로 수행하면 '1'을, 그렇지 않으면
// '0'을 리턴한다.
int writeRecord(FILE *fp, const STUDENT *s, int rrn);
void pack(char *recordbuf, const STUDENT *s);

// 함수 appendRecord()는 학생 레코드 파일에 새로운 레코드를 append한다.
// 레코드 파일에 레코드가 하나도 존재하지 않는 경우 (첫 번째 append)는 header
// 레코드를 파일에 생성하고 첫 번째 레코드를 저장한다. 당연히 레코드를 append를
// 할 때마다 header 레코드에 대한 수정이 뒤따라야 한다. 함수 appendRecord()는
// 내부적으로 writeRecord() 함수를 호출하여 레코드 저장을 해결한다. 성공적으로
// 수행하면 '1'을, 그렇지 않으면 '0'을 리턴한다.
int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr,
                 char *email);

// 학생 레코드 파일에서 검색 키값을 만족하는 레코드가 존재하는지를 sequential
// search 기법을 통해 찾아내고, 이를 만족하는 모든 레코드의 내용을 출력한다.
// 검색 키는 학생 레코드를 구성하는 어떤 필드도 가능하다. 내부적으로
// readRecord() 함수를 호출하여 sequential search를 수행한다. 검색 결과를 출력할
// 때 반드시 printRecord() 함수를 사용한다. (반드시 지켜야 하며, 그렇지 않는
// 경우 채점 프로그램에서 자동적으로 틀린 것으로 인식함)
void searchRecord(FILE *fp, FIELD f, char *keyval);
void printRecord(const STUDENT *s);

// 레코드의 필드명을 enum FIELD 타입의 값으로 변환시켜 준다.
// 예를 들면, 사용자가 수행한 명령어의 인자로 "NAME"이라는 필드명을 사용하였다면
// 프로그램 내부에서 이를 NAME(=1)으로 변환할 필요성이 있으며, 이때 이 함수를
// 이용한다.
FIELD getFieldID(char *fieldname);

void main(int argc, char *argv[]) {
    FILE *fp;  // 모든 file processing operation은 C library를 사용할 것
    if (argc < 4) {
        fprintf(stderr, "input is too small!\n");
        return;
    }

    if (!strcmp(argv[1], "-a")) {
        if ((fp = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "can't open file!");
            return;
        }
        appendRecord(fp, argv[3], argv[4], argv[5], argv[6], argv[7]);
    } else if (!strcmp(argv[1], "-s")) {
        if ((fp = fopen(argv[2], "w+")) == NULL) {
            fprintf(stderr, "can't open file!");
            return;
        }
        char tempstr1[STRING_LEN];
        char tempstr2[STRING_LEN];
        memset(tempstr1, 0, sizeof(STRING_LEN) * sizeof(char));
        memset(tempstr1, 0, sizeof(STRING_LEN) * sizeof(char));
        int cnt = 0;
        while (TRUE) {
            if (argv[3][cnt] == '=') break;
            cnt++;
        }
        memcpy(tempstr1, argv[3], cnt * sizeof(char));
        memcpy(tempstr2, argv[3] + (cnt + 1),
               (strlen(argv[3]) - (cnt + 1)) * sizeof(char));
        searchRecord(fp, getFieldID(tempstr1), tempstr2);
    } else {
        fprintf(stderr, "wrong input option!");
        return;
    }
    fclose(fp);
    return;
}

void unpack(const char *recordbuf, STUDENT *s) {
    memcpy(s->id, recordbuf, ID_LEN);
    memcpy(s->name, recordbuf + 1 + ID_LEN, NAME_LEN);
    memcpy(s->dept, recordbuf + 2 + ID_LEN + NAME_LEN, DEPT_LEN);
    memcpy(s->addr, recordbuf + 3 + ID_LEN + NAME_LEN + DEPT_LEN, ADDR_LEN);
    memcpy(s->email, recordbuf + 4 + ID_LEN + NAME_LEN + DEPT_LEN + ADDR_LEN,
           EMAIL_LEN);
}

void pack(char *recordbuf, const STUDENT *s) {
    memcpy(recordbuf, s->id, ID_LEN);
    memcpy(recordbuf + ID_LEN, "#", 1);
    memcpy(recordbuf + 1 + ID_LEN, s->name, NAME_LEN);
    memcpy(recordbuf + 1 + ID_LEN + NAME_LEN, "#", 1);
    memcpy(recordbuf + 2 + ID_LEN + NAME_LEN, s->dept, DEPT_LEN);
    memcpy(recordbuf + 2 + ID_LEN + NAME_LEN + DEPT_LEN, "#", 1);
    memcpy(recordbuf + 3 + ID_LEN + NAME_LEN + DEPT_LEN, s->addr, ADDR_LEN);
    memcpy(recordbuf + 3 + ID_LEN + NAME_LEN + DEPT_LEN + ADDR_LEN, "#", 1);
    memcpy(recordbuf + 4 + ID_LEN + NAME_LEN + DEPT_LEN + ADDR_LEN, s->email,
           EMAIL_LEN);
    memcpy(recordbuf + 4 + ID_LEN + NAME_LEN + DEPT_LEN + ADDR_LEN + EMAIL_LEN,
           "#", 1);
}

void searchRecord(FILE *fp, FIELD f, char *keyval) {
    STUDENT stu;
    int header[2];
    fseek(fp, 0, SEEK_SET);
    fread(header, sizeof(int), 2, fp);
    for (int i = 0; i < header[0]; i++) {
        if (!readRecord(fp, &stu, i)) {
            fprintf(stderr, "searching error!");
            return;
        }
        switch (f) {
            case ID:
                if (!strcmp(keyval, stu.id)) printRecord(&stu);
                break;
            case NAME:
                if (!strcmp(keyval, stu.name)) printRecord(&stu);
                break;
            case DEPT:
                if (!strcmp(keyval, stu.dept)) printRecord(&stu);
                break;
            case ADDR:
                if (!strcmp(keyval, stu.addr)) printRecord(&stu);
                break;
            case EMAIL:
                if (!strcmp(keyval, stu.email)) printRecord(&stu);
                break;
        }
    }
}

int appendRecord(FILE *fp, char *id, char *name, char *dept, char *addr,
                 char *email) {
    STUDENT newStudent;
    char recordbuf[RECORD_SIZE];
    int header[2];

    // newStudent init
    strcpy(newStudent.id, id);
    strcpy(newStudent.name, name);
    strcpy(newStudent.dept, dept);
    strcpy(newStudent.addr, addr);
    strcpy(newStudent.email, email);

    // if file is empty
    if (!fread(header, sizeof(int), 2, fp)) {
        header[0] = 1;
        header[1] = -1;
        if (!fwrite(header, sizeof(int) * 2, 1, fp)) {
            fprintf(stderr, "new record header save error!");
            return 0;
        }
        if (!writeRecord(fp, &newStudent, 0)) {
            fprintf(stderr, "record writing error!");
            return 0;
        }
    } else {
        int rrn = header[0];
        header[0]++;
        fseek(fp, 0, SEEK_SET);
        if (!fwrite(header, sizeof(int) * 2, 1, fp)) {
            fprintf(stderr, "new record header save error!");
            return 0;
        }
        if (!writeRecord(fp, &newStudent, rrn + 1)) {
            fprintf(stderr, "record writing error!");
            return 0;
        }
    }
}

int readRecord(FILE *fp, STUDENT *s, int rrn) {
    fseek(fp, sizeof(int) * 2 + rrn * RECORD_SIZE, SEEK_SET);
    char recordbuf[RECORD_SIZE];

    if (fread(recordbuf, RECORD_SIZE, 1, fp) == 0) {
        fprintf(stderr, "Reading error in readRecord function!");
        return 0;
    }
    unpack(recordbuf, s);
    return 1;
}

int writeRecord(FILE *fp, const STUDENT *s, int rrn) {
    fseek(fp, sizeof(int) * 2 + rrn * RECORD_SIZE, SEEK_SET);
    char recordbuf[RECORD_SIZE];
    pack(recordbuf, s);
    if (fwrite(recordbuf, sizeof(RECORD_SIZE), 1, fp) == 0) {
        fprintf(stderr, "Writing error in writeRecord function!");
        return 0;
    }
    return 1;
}

FIELD getFieldID(char *fieldname) {
    if (!strcmp(fieldname, "ID")) {
        return ID;
    } else if (!strcmp(fieldname, "NAME")) {
        return NAME;
    } else if (!strcmp(fieldname, "DEPT")) {
        return DEPT;
    } else if (!strcmp(fieldname, "ADDR")) {
        return ADDR;
    } else if (!strcmp(fieldname, "EMAIL")) {
        return EMAIL;
    } else {  //예외 상황(없을 경우를 대비)
        return -1;
    }
}

void printRecord(const STUDENT *s) {
    printf("%s | %s | %s | %s | %s\n", s->id, s->name, s->dept, s->addr,
           s->email);
}
