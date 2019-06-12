/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <tree_sitter/api.h>
#include <cstring>
/* Header for class jsitter_interop_JSitter */

struct TSZipper {
    TSTreeCursor cursor;
    uint32_t start_byte;
    uint32_t end_byte;
    const void *id;
    TSSymbol symbol;
};


TSZipper *new_zipper(TSNode root) {
    TSZipper *new_zipper = (TSZipper *)malloc(sizeof(TSZipper));
    TSTreeCursor c = ts_tree_cursor_new(root);
    new_zipper->cursor = c;
    new_zipper->start_byte = ts_node_start_byte(root);
    new_zipper->end_byte = ts_node_end_byte(root);
    new_zipper->symbol = ts_node_symbol(root);
    new_zipper->id = root.id;
    return new_zipper;
}

const int UP = 0;
const int DOWN = 1;
const int RIGHT = 3;
const int NEXT = 4;

template<int dir>
bool cursor_move(TSTreeCursor *cursor);

template<>
bool cursor_move<UP>(TSTreeCursor *cursor) {
    return ts_tree_cursor_goto_parent(cursor);
}

template<>
bool cursor_move<DOWN>(TSTreeCursor *cursor) {
    return ts_tree_cursor_goto_first_child(cursor);
}

template<>
bool cursor_move<RIGHT>(TSTreeCursor *cursor) {
    return ts_tree_cursor_goto_next_sibling(cursor);
}

template<>
bool cursor_move<NEXT>(TSTreeCursor *cursor) {
    if (ts_tree_cursor_goto_first_child(cursor)) {
        return true;
    } else if (ts_tree_cursor_goto_next_sibling(cursor)) {
        return true;
    } else {
        while (ts_tree_cursor_goto_parent(cursor)) {
            if (ts_tree_cursor_goto_next_sibling(cursor)) {
                return true;
            }
        }
        return false;
    }
}

template<int dir>
bool zipper_move(TSZipper *zip, bool toSymbol,  TSSymbol symbol, bool named) {
    TSNode current = ts_tree_cursor_current_node(&zip->cursor);
    if (toSymbol) {
        while (cursor_move<dir>(&zip->cursor)) {
            TSNode node = ts_tree_cursor_current_node(&zip->cursor);
            if (ts_node_symbol(node) == symbol) {
                zip->symbol = ts_node_symbol(node);
                zip->start_byte = ts_node_start_byte(node);
                zip->end_byte = ts_node_end_byte(node);
                zip->id = node.id;
                return true;
            }
        }
        ts_tree_cursor_reset(&zip->cursor, current);
        return false;
    } else if (named) {
        while (cursor_move<dir>(&zip->cursor)) {
            TSNode node = ts_tree_cursor_current_node(&zip->cursor);
            if (ts_node_is_named(node)) {
                zip->symbol = ts_node_symbol(node);
                zip->start_byte = ts_node_start_byte(node);
                zip->end_byte = ts_node_end_byte(node);
                zip->id = node.id;
                return true;
            }
        }
        ts_tree_cursor_reset(&zip->cursor, current);
        return false;
    } else {
        if (cursor_move<dir>(&zip->cursor)) {
            TSNode node = ts_tree_cursor_current_node(&zip->cursor);
            zip->symbol = ts_node_symbol(node);
            zip->start_byte = ts_node_start_byte(node);
            zip->end_byte = ts_node_end_byte(node);
            zip->id = node.id;
            return true;
        } else {
            return false;
        }
    }
}

TSZipper *copy_zipper(TSZipper *zip) {
    return new_zipper(ts_tree_cursor_current_node(&zip->cursor));
}

bool zipper_move(TSZipper *zip, int dir, bool to_symbol, TSSymbol symbol, bool named) {
    switch (dir) {
        case UP:
            return zipper_move<UP>(zip, to_symbol, symbol , named);
        case DOWN:
            return zipper_move<DOWN>(zip, to_symbol, symbol , named);
        case RIGHT:
            return zipper_move<RIGHT>(zip, to_symbol, symbol , named);
        case NEXT:
            return zipper_move<NEXT>(zip, to_symbol, symbol , named);
        default:
            abort();
    }
}

#ifdef __cplusplus
extern "C" {
#endif
    
    TSLanguage *tree_sitter_go();
    
    TSLanguage *tree_sitter_json();
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    copyCursor
     * Signature: (J)J
     */
    JNIEXPORT jlong JNICALL Java_jsitter_interop_JSitter_copyCursor
    (JNIEnv *, jclass, jlong zipper_ptr) {
        return (jlong) copy_zipper((TSZipper *)zipper_ptr);
    }
    
    JNIEXPORT jlong JNICALL JavaCritical_jsitter_interop_JSitter_copyCursor
    (jlong zipper_ptr) {
        return (jlong) copy_zipper((TSZipper *)zipper_ptr);
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    move
     * Signature: (JISZ)Z
     */
    JNIEXPORT jboolean JNICALL Java_jsitter_interop_JSitter_move
    (JNIEnv *, jclass, jlong zipper_ptr, jint dir, jboolean toSymbol, jshort ts_symbol, jboolean named) {
        return zipper_move((TSZipper *)zipper_ptr, dir, toSymbol, (TSSymbol)ts_symbol, named);
    }
    
    JNIEXPORT jboolean JNICALL JavaCritical_jsitter_interop_JSitter_move
    (jlong zipper_ptr, jint dir, jboolean toSymbol, jshort ts_symbol, jboolean named) {
        return zipper_move((TSZipper *)zipper_ptr, dir, toSymbol, (TSSymbol)ts_symbol, named);
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    getSymbolName
     * Signature: (JS)Ljava/lang/String;
     */
    JNIEXPORT jstring JNICALL Java_jsitter_interop_JSitter_getSymbolName
    (JNIEnv *env, jclass, jlong language_ptr, jshort ts_symbol) {
        const char *name = ts_language_symbol_name((TSLanguage *)language_ptr, (TSSymbol)ts_symbol);
        return env->NewStringUTF(name);
    }
    
    JNIEXPORT jstring JNICALL Java_jsitter_interop_JSitter_getName
    (JNIEnv *env, jclass, jlong zipper_ptr) {
        TSZipper *zip = (TSZipper *)zipper_ptr;
        TSNode node = ts_tree_cursor_current_node(&zip->cursor);
        const char *name = ts_node_type(node);
        return env->NewStringUTF(name);
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    isTerminal
     * Signature: (JS)Z
     */
    JNIEXPORT jboolean JNICALL Java_jsitter_interop_JSitter_isTerminal
    (JNIEnv *, jclass, jlong language_ptr, jshort ts_symbol) {
        return ts_language_symbol_type((TSLanguage*)language_ptr, (TSSymbol)ts_symbol) == TSSymbolTypeAnonymous;
    }
    
    JNIEXPORT jboolean JNICALL JavaCritical_jsitter_interop_JSitter_isTerminal
    (jlong language_ptr, jshort ts_symbol) {
        return ts_language_symbol_type((TSLanguage*)language_ptr, (TSSymbol)ts_symbol) == TSSymbolTypeAnonymous;
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    getSymbolByName
     * Signature: (JLjava/lang/String;)S
     */
    JNIEXPORT jshort JNICALL Java_jsitter_interop_JSitter_getSymbolByName
    (JNIEnv *env, jclass, jlong language_ptr, jstring name) {
        jboolean copy;
        const char *chars = env->GetStringUTFChars(name, &copy);
        TSSymbol symbol = ts_language_symbol_for_name((TSLanguage *)language_ptr, chars);
        if (copy) {
            env->ReleaseStringUTFChars(name, chars);
        }
        return symbol;
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    releaseTree
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_jsitter_interop_JSitter_releaseTree
    (JNIEnv *, jclass, jlong tree_ptr) {
        ts_tree_delete((TSTree *)tree_ptr);
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    releaseParser
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_jsitter_interop_JSitter_releaseParser
    (JNIEnv *, jclass, jlong parser_ptr) {
        ts_parser_delete((TSParser *)parser_ptr);
    }
    
    struct Input {
        JNIEnv *env;
        jobject input;
        jmethodID read_mtd;
        const char *reading_addr;
    };
    
    const char *input_jni_read(void *payload, uint32_t byte_index, TSPoint position, uint32_t *bytes_read) {
        Input *input = (Input *)payload;
        jint read = input->env->CallIntMethod(input->input, input->read_mtd, byte_index);
        *bytes_read = read;
        return input->reading_addr;
    }
    
    static jmethodID read_mtd = 0;
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    parse
     * Signature: (JJLjsitter/interop/JSitter/Input;JIII)J
     */
    JNIEXPORT jlong JNICALL Java_jsitter_interop_JSitter_parse
    (JNIEnv *env, jclass, jlong parser_ptr, jlong old_tree_ptr, jobject input, jint encoding, jlong reading_addr, jint start_byte, jint old_end_byte, jint new_end_byte) {
        if (read_mtd == 0) {
            jclass input_class = env->FindClass("jsitter/interop/JSitter$Input");
            read_mtd = env->GetMethodID(input_class, "read", "(I)I");
        }
        
        Input input_ctx;
        input_ctx.env = env;
        input_ctx.input = input;
        input_ctx.read_mtd = read_mtd;
        input_ctx.reading_addr = (const char *)reading_addr;
        
        TSInput ts_input;
        ts_input.encoding = (TSInputEncoding)encoding;
        ts_input.payload = &input_ctx;
        ts_input.read = &input_jni_read;
        
        TSParser *parser = (TSParser *)parser_ptr;
        if (old_tree_ptr) {
            TSTree *old_tree = (TSTree *)old_tree_ptr;
            TSTree *old_tree_copy = ts_tree_copy(old_tree);
            TSInputEdit edit;
            edit.start_byte = start_byte;
            edit.old_end_byte = old_end_byte;
            edit.new_end_byte = new_end_byte;
            ts_tree_edit(old_tree_copy, &edit);
            
            TSTree *new_tree = ts_parser_parse(parser, old_tree_copy, ts_input);
            ts_tree_delete(old_tree_copy);
            return (jlong)new_tree;
        } else {
            return (jlong) ts_parser_parse(parser, NULL, ts_input);
        }
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    releaseZipper
     * Signature: (J)V
     */
    JNIEXPORT void JNICALL Java_jsitter_interop_JSitter_releaseZipper
    (JNIEnv *, jclass, jlong zipper_ptr) {
        TSZipper *zip = (TSZipper *)zipper_ptr;
        ts_tree_cursor_delete(&zip->cursor);
        free(zip);
    }
    
    JNIEXPORT void JNICALL JavaCritical_jsitter_interop_JSitter_releaseZipper
    (jlong zipper_ptr) {
        TSZipper *zip = (TSZipper *)zipper_ptr;
        ts_tree_cursor_delete(&zip->cursor);
        free(zip);
    }

    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    makeCursor
     * Signature: (J)J
     */
    JNIEXPORT jlong JNICALL Java_jsitter_interop_JSitter_makeCursor
    (JNIEnv *, jclass, jlong tree_ptr) {
        TSTree *tree = (TSTree *)tree_ptr;
        TSNode root = ts_tree_root_node(tree);
        return (jlong)new_zipper(root);
    }
    
    JNIEXPORT jlong JNICALL JavaCritical_jsitter_interop_JSitter_makeCursor
    (jlong tree_ptr) {
        TSTree *tree = (TSTree *)tree_ptr;
        TSNode root = ts_tree_root_node(tree);
        return (jlong)new_zipper(root);
    }
    
    /*
     * Class:     jsitter_interop_JSitter
     * Method:    newParser
     * Signature: (J)J
     */
    JNIEXPORT jlong JNICALL Java_jsitter_interop_JSitter_newParser
    (JNIEnv *, jclass, jlong language_ptr) {
        TSParser *parser = ts_parser_new();
        ts_parser_set_language(parser, (TSLanguage *)language_ptr);
        return (jlong) parser;
    }
    
    JNIEXPORT jlong JNICALL JavaCritical_jsitter_interop_JSitter_newParser
    (jlong language_ptr) {
        TSParser *parser = ts_parser_new();
        ts_parser_set_language(parser, (TSLanguage *)language_ptr);
        return (jlong) parser;
    }
    
    JNIEXPORT jlong JNICALL Java_jsitter_interop_JSitter_findLanguage
    (JNIEnv *env, jclass, jstring name) {
        jboolean copy;
        const char *language_name = env->GetStringUTFChars(name, &copy);
        TSLanguage *lang = NULL;
        if (!strcmp(language_name, "go")) {
            lang = tree_sitter_go();
        } else if (!strcmp(language_name, "json")) {
            lang = tree_sitter_json();
        }
        if (copy) {
            env->ReleaseStringUTFChars(name, language_name);
        }
        return (jlong) lang;
    }
    
#ifdef __cplusplus
}
#endif
