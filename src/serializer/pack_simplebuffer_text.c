#define MAX_PRINT_VALUE_LENGTH (1024)
#define MAX_NEST_LEVEL         (50)

typedef enum
{
    T_NORMAL,
    T_ARRAY,
    T_STRUCT,
    T_STRING,
    T_RAW,
    T_NONE
} array_type_t;

struct nest_info_t
{
    array_type_t type;
    int num_of_element;
    int offset;
};

typedef enum 
{
    PACK_STATE_NORMAL,
    PACK_STATE_STRING,
    PACK_STATE_STRING_ESCAPE,
    PACK_STATE_RAW,
    END_OF_PACK_STATE
} pack_state_t;

#if 0
static void pack_simplebuffer_text_sub( simplebuffer dump,
                                        size_t start,
                                        size_t end,
                                        array_type_t type,
                                        pack_state_t initial_state )
{
    size_t i;
    pack_state_t state = initial_state;
    pack_state_t next_state = initial_state;
    simplebuffer token = {0};

    struct nest_info_t nest[ (int)MAX_NEST_LEVEL ] = { {(array_type_t)0} };
    size_t nestlevel = 0;
    nest[nestlevel].type = type;
    
    char recent_char = 0;
    for( i = start; i < end; i++ )
    {
        char c = dump.data[i];
        if( state == PACK_STATE_NORMAL )
        {
            if( character_is_splitter( c ) )
            {
                check_token(pk, &token, nest, nestlevel);
            }
            else if( c == braceopen[0] )
            {
                check_token(pk, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_ARRAY;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
            }
            else if( c == braceopen[1] )
            {
                check_token(pk, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_STRUCT;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
            }
            else if( c == braceclose[0] )
            {
                check_token(pk, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    msgpack_pack_array( pk, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( dump, nest[nestlevel].offset+1, i, T_ARRAY, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
            }
            else if( c == braceclose[1] )
            {
                check_token(pk, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    msgpack_pack_nil(pk);
                    msgpack_pack_array(pk, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( dump, nest[nestlevel].offset+1, i, T_STRUCT, state );
                }
                
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
            }
            else if( c == '"' )
            {
                check_token(pk, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_STRING;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
                next_state = PACK_STATE_STRING;
            }
            else if( c == '<' )
            {
                check_token(pk, &token, nest, nestlevel);
                nestlevel += 1;
                nest[nestlevel].type = T_RAW;
                nest[nestlevel].num_of_element = 0;
                nest[nestlevel].offset = i;
                next_state = PACK_STATE_RAW;
            }
            else
            {
                simplebuffer_write( &token, &c, 1 );
            }
        }
        else if( state == PACK_STATE_STRING )
        {
            if( c == '\\' )
            {
                next_state = PACK_STATE_STRING_ESCAPE;
            }
            else if( c == '"' )
            {
                check_token(pk, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    pack_simplebuffer_text_sub( dump, nest[nestlevel].offset+1, i, T_STRING, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
                next_state = PACK_STATE_NORMAL;
            }
            else
            {
                simplebuffer_write( &token, &c, 1 );
            }
        }
        else if( state == PACK_STATE_STRING_ESCAPE )
        {
            simplebuffer_write( &token, &c, 1 );
            next_state = PACK_STATE_STRING;
        }
        else if( state == PACK_STATE_RAW )
        {
            if( character_is_splitter( c ) )
            {
                check_token(pk, &token, nest, nestlevel);
            }
            else if( c == '>' )
            {
                check_token(pk, &token, nest, nestlevel);
                if( nestlevel == 1 )
                {
                    msgpack_pack_raw(pk, (int)nest[nestlevel].num_of_element);
                    pack_simplebuffer_text_sub( dump, nest[nestlevel].offset+1, i, T_RAW, state );
                }
                nestlevel -= 1;
                nest[nestlevel].num_of_element += 1;
                next_state = PACK_STATE_NORMAL;
            }
            else
            {
                simplebuffer_write( &token, &c, 1 );
            }
        }
        state = next_state;
        recent_char = c;
    }
    check_token(pk, &token, nest, nestlevel);
}

simplebuffer pack_simplebffer_text( char *text )
{
    simplebuffer serialized;
    simplebuffer_init( &serialized );
    pack_simplebffer_text_sub( &serialized, text, 0, strlen( text ), T_NORMAL, PACK_STATE_NORMAL );

    return serialized;
}


#endif
