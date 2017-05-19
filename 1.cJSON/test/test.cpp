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

int main() {

    //JSON字符串解析,增,删,改测试
    // test_parse_and_change();

    //JSON数组相关操作测试
    test_array_and_other();
    
    
    
    return 0;
}
