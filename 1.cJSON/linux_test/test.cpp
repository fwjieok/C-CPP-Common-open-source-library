#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cjson/cJSON.h"
#include "cjson/cJSON_Utils.h"

void test_parse_and_change() {
    char my_json_string[] = "{\
     \"name\": \"Jack (\'Bee\') Nimble\",\
     \"format\": {\
        \"type\":       \"rect\",\
        \"width\":      1920,\
        \"height\":     1080,\
        \"interlace\":  false,\
        \"frame rate\": 24\
     }\
    }";

    const char *version = cJSON_Version();
    printf("----------- %s ----------------\n", version);
    
    cJSON *root   = cJSON_Parse(my_json_string);
    if (!root) {
        printf("cJSON_Parse Error: %s\n", cJSON_GetErrorPtr());
    } else {
        cJSON *name   = cJSON_GetObjectItem(root, "name");
        cJSON *format = cJSON_GetObjectItemCaseSensitive(root, "format");
        cJSON *framerate_item = cJSON_GetObjectItemCaseSensitive(format, "frame rate");
        double framerate = 0;

        if (cJSON_IsNumber(framerate_item)) {
            cJSON_SetNumberValue(framerate_item, 25);
            framerate = framerate_item->valuedouble;
            printf("framerate: %f\n", framerate);
        }

        //修改字段(Item)——先删除,再添加
        if (cJSON_IsString(name)) {
            printf("name: %s\n", name->valuestring);
            cJSON *name_new = cJSON_CreateString("fanwenjie");
            cJSON_DeleteItemFromObject(root, "name");
            cJSON_AddItemToObject(root, "name", name_new);
        }

        //添加字段(Item)——不存在,再添加
        if (!cJSON_HasObjectItem(root, "address")) {
            printf("json root hasn\'t item address\n");
            cJSON *address = cJSON_CreateString("China ShenZhen");
            cJSON_AddItemToObject(root, "address", address);
        }

        //cJSON可以添加重复字段,所以在添加前先用HasObjectItem判断
        cJSON *address = cJSON_CreateString("China BeiJing");
        cJSON_AddItemToObject(root, "address", address);

        //删除字段(有两个address字段,会删除第一个)
        cJSON_DeleteItemFromObject(root, "address");
            
        char *render = cJSON_Print(root);

        printf("------------------------------------\n\n");
        printf("%s\n", render);

        printf("--------- Minify -------------------\n\n");
        cJSON_Minify(render);
        printf("%s\n\n", render);

        cJSON_Delete(root);
        free(render);
    }
}


void test_json_string_create() {

    cJSON *root;
    cJSON *fmt;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddFalseToObject (fmt, "interlace");
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    cJSON_AddItemToObject(root, "address", cJSON_CreateString("China ShenZhen"));
    
    char *render = cJSON_Print(root);
    
    printf("------------------------------------\n\n");
    printf("%s\n", render);

    printf("--------- Minify -------------------\n\n");
    cJSON_Minify(render);
    printf("%s\n\n", render);

    cJSON_Delete(root);
    free(render);
}


void test_create_and_modify_array() {
    cJSON *root = cJSON_CreateObject();

    /*
      一：简单的JSON数组
      输出格式：{"key":["value1","value2","value3"....]}
    */
    char addressArray[][20] = {"BenJing", "ShangHai", "ShenZhen"};

    cJSON *address = cJSON_CreateArray();
    cJSON_AddStringToObject(root, "name", "fanwenjieok");
    cJSON_AddItemToObject(root, "address", address);
    for (int i = 0; i < 3; i ++) {
        cJSON_AddItemToArray(address, cJSON_CreateString(addressArray[i]));
    }

    //根据索引修改json数组元素
    cJSON_ReplaceItemInArray(address, 2, cJSON_CreateString("GuangZhou"));

    /*
      二：复杂的JSON数组(JSON数组元素也是一个JSON对像)
      输出格式：{"key":[{"key1":"value1", "key2":"value2"}...]}
     */
    cJSON *blogs = cJSON_CreateArray();

    for (int i = 0; i < 3; i ++) {
        //1.创建JSON对像
        cJSON *blog = cJSON_CreateObject();
        cJSON_AddStringToObject(blog, "title", "titleXXX");
        cJSON_AddStringToObject(blog, "url",   "urlXXX");

        //2.将JSON对像作为元素添加进JSON数组
        cJSON_AddItemToArray(blogs, blog);
    }
    
    //将JSON数组添加进JSON根对像
    cJSON_AddItemToObject(root, "blogs", blogs);
    
    char *render = cJSON_Print(root);

    printf("%s\n\n", render);
    printf("--------- Minify -------------------\n\n");
    cJSON_Minify(render);
    printf("%s\n\n", render);
    
    cJSON_Delete(root);
    free(render);
}

void test_parse_json_array() {
    char my_json_string[] = "{\
     \"name\": \"Jack (\'Bee\') Nimble\",\
     \"address\": [\"BeiJing\", \"ShangHai\", \"ShenZhen\"],\
     \"blogs\":[{\"title\":\"title001\", \"url\":\"url001\"},\
                {\"title\":\"title002\", \"url\":\"url002\"},\
                {\"title\":\"title003\", \"url\":\"url003\"}]\
    }";

    cJSON *root   = cJSON_Parse(my_json_string);
    if (!root) {
        printf("cJSON_Parse Error: %s\n", cJSON_GetErrorPtr());
    } else {
        cJSON *name    = cJSON_GetObjectItem(root, "name");
        cJSON *address = cJSON_GetObjectItem(root, "address");
        cJSON *blogs   = cJSON_GetObjectItem(root, "blogs");

        //解析简单的JSON数组
        if (cJSON_IsArray(address)) {
            int size = cJSON_GetArraySize(address);
            for (int i = 0; i < size; i ++) {
                cJSON *item = cJSON_GetArrayItem(address, i);
                if (item == NULL) {
                    printf("cJSON_GetArrayItem Error: %s\n", cJSON_GetErrorPtr());
                    break;
                }
                if (cJSON_IsString(item)) {
                    printf("%d: %s\n", i, item->valuestring);
                }
            }
        }

        //解析复杂的JSON数组
        cJSON *blog;
        int   count = 0;
        if (cJSON_IsArray(blogs)) {
            int size = cJSON_GetArraySize(blogs);
            printf("------------ size: %d ------------\n", size);
            //遍历数组
            cJSON_ArrayForEach(blog, blogs) {
                if (cJSON_IsObject(blog)) {
                    cJSON *title = cJSON_GetObjectItem(blog, "title");
                    cJSON *url   = cJSON_GetObjectItem(blog, "url");
                    count ++;
                    printf("title%d: %s, url%d: %s\n", count, title->valuestring, count, url->valuestring);
                }
            }
        }
        
        char *render = cJSON_Print(root);
        printf("--------- Minify -------------------\n\n");
        cJSON_Minify(render);
        printf("%s\n\n", render);

        cJSON_Delete(root);
        free(render);
    }
}

int main() {

    //JSON字符串解析,增,删,改测试
    // test_parse_and_change();

    //JSON字符串创建
    // test_json_string_create();
    
    //JSON数组创建
    // test_create_and_modify_array();

    //JSON数组解析提取
    test_parse_json_array();
    
    
    return 0;
}
