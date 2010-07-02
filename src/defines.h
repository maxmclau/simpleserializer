#ifndef H_DEFINES_H_100629201617__
#define H_DEFINES_H_100629201617__

#define TYPE_POSITIVE_FIXNUM       (0x00)
#define TYPE_POSITIVE_FIXNUM_MASK  (0x80)

#define TYPE_NEGATIVE_FIXNUM       (0xe0)
#define TYPE_NEGATIVE_FIXNUM_MASK  (0xe0)

#define TYPE_FIXROW                (0xa0)
#define TYPE_FIXROW_MASK           (0xe0)

#define TYPE_FIXARRAY              (0x90)
#define TYPE_FIXARRAY_MASK         (0xe0)

#define TYPE_FIXMAP                (0x80)
#define TYPE_FIXMAP_MASK           (0xe0)

#define TYPE_VALIABLE              (0xc0)
#define TYPE_VALIABLE_MASK         (0xe0)

#define TYPE_VALIABLE_NIL     (0xc0) ///< シリアライズデータヘッダ(NIL     )
#define TYPE_VALIABLE_FALSE   (0xc4) ///< シリアライズデータヘッダ(FALSE   )
#define TYPE_VALIABLE_TRUE    (0xc8) ///< シリアライズデータヘッダ(TRUE    )

#define TYPE_VALIABLE_FLOAT   (0xca) ///< シリアライズデータヘッダ(FLOAT   )
#define TYPE_VALIABLE_DOUBLE  (0xcb) ///< シリアライズデータヘッダ(DOUBLE  )

#define TYPE_VALIABLE_UINT8   (0xcc) ///< シリアライズデータヘッダ(UINT8   )
#define TYPE_VALIABLE_UINT16  (0xcd) ///< シリアライズデータヘッダ(UINT16  )
#define TYPE_VALIABLE_UINT32  (0xce) ///< シリアライズデータヘッダ(UINT32  )
#define TYPE_VALIABLE_UINT64  (0xcf) ///< シリアライズデータヘッダ(UINT64  )

#define TYPE_VALIABLE_INT8    (0xd0) ///< シリアライズデータヘッダ(INT8    )
#define TYPE_VALIABLE_INT16   (0xd1) ///< シリアライズデータヘッダ(INT16   )
#define TYPE_VALIABLE_INT32   (0xd2) ///< シリアライズデータヘッダ(INT32   )
#define TYPE_VALIABLE_INT64   (0xd3) ///< シリアライズデータヘッダ(INT64   )

#define TYPE_VALIABLE_RAW16   (0xc1) ///< シリアライズデータヘッダ(RAW16   )
#define TYPE_VALIABLE_RAW32   (0xc2) ///< シリアライズデータヘッダ(RAW32   )

#define TYPE_VALIABLE_ARRAY16 (0xc5) ///< シリアライズデータヘッダ(ARRAY16 )
#define TYPE_VALIABLE_ARRAY32 (0xc6) ///< シリアライズデータヘッダ(ARRAY32 )

#define TYPE_VALIABLE_MAP16   (0xd5) ///< シリアライズデータヘッダ(MAP16   )
#define TYPE_VALIABLE_MAP32   (0xd6) ///< シリアライズデータヘッダ(MAP32   )

#endif //H_DEFINES_H_100629201617__
