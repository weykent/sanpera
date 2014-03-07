// TODO comment out stuff that doesn't exist in older ImageMagick
// =============================================================================
// -----------------------------------------------------------------------------
// stdlib

FILE *fdopen(int fd, const char *mode);


// =============================================================================
// -----------------------------------------------------------------------------
// forward declarations

struct _Image;
typedef struct _Image Image;
struct _ImageInfo;
typedef struct _ImageInfo ImageInfo;
typedef ... CacheView;




// =============================================================================
// independent stuff
// -----------------------------------------------------------------------------
// version.h
// (done)

const char *GetMagickCopyright();
const char *GetMagickFeatures();
char *GetMagickHomeURL();
const char *GetMagickPackageName();
const char *GetMagickQuantumDepth(size_t *);
const char *GetMagickQuantumRange(size_t *);
const char *GetMagickReleaseDate();
const char *GetMagickVersion(size_t *);


// =============================================================================
// core types
// -----------------------------------------------------------------------------
// MagickCore.h

static const int MaxTextExtent;

// -----------------------------------------------------------------------------
// magick-type.h

// actually macros, but cffi figures it out
static const int MAGICKCORE_QUANTUM_DEPTH;
static float const QuantumRange;
static char *const QuantumFormat;

typedef unsigned int MagickStatusType;

// Plain numeric types that vary in size depending on build; these cannot be
// accessed directly with cffi.  They're declared as structs so cffi will
// figure out the sizes and we can create them from C
typedef struct { ...; } MagickRealType;
typedef struct { ...; } Quantum;

// XXX this also varies in size, sigh
typedef unsigned long long MagickSizeType;

typedef enum {
    UndefinedChannel,
    RedChannel,
    GrayChannel,
    CyanChannel,
    GreenChannel,
    MagentaChannel,
    BlueChannel,
    YellowChannel,
    AlphaChannel,
    OpacityChannel,
    BlackChannel,
    IndexChannel,
    CompositeChannels,
    AllChannels,
    TrueAlphaChannel, /* extract actual alpha channel from opacity */
    RGBChannels,      /* set alpha from  grayscale mask in RGB */
    GrayChannels,
    SyncChannels,     /* channels should be modified equally */
    DefaultChannels,
    ...
} ChannelType;

typedef enum {
    UndefinedClass,
    DirectClass,
    PseudoClass
} ClassType;

typedef enum {
    MagickFalse = 0,
    MagickTrue = 1
} MagickBooleanType;

// TODO mooore
//
// TODO forward decls actually go here


// -----------------------------------------------------------------------------
// memory_.h

void RelinquishMagickMemory(void *);


// -----------------------------------------------------------------------------
// exception.h

typedef enum {
    UndefinedException,
    WarningException,
    ResourceLimitWarning,
    TypeWarning,
    OptionWarning,
    DelegateWarning,
    MissingDelegateWarning,
    CorruptImageWarning,
    FileOpenWarning,
    BlobWarning,
    StreamWarning,
    CacheWarning,
    CoderWarning,
    FilterWarning,
    ModuleWarning,
    DrawWarning,
    ImageWarning,
    WandWarning,
    RandomWarning,
    XServerWarning,
    MonitorWarning,
    RegistryWarning,
    ConfigureWarning,
    PolicyWarning,
    ErrorException,
    ResourceLimitError,
    TypeError,
    OptionError,
    DelegateError,
    MissingDelegateError,
    CorruptImageError,
    FileOpenError,
    BlobError,
    StreamError,
    CacheError,
    CoderError,
    FilterError,
    ModuleError,
    DrawError,
    ImageError,
    WandError,
    RandomError,
    XServerError,
    MonitorError,
    RegistryError,
    ConfigureError,
    PolicyError,
    FatalErrorException,
    ResourceLimitFatalError,
    TypeFatalError,
    OptionFatalError,
    DelegateFatalError,
    MissingDelegateFatalError,
    CorruptImageFatalError,
    FileOpenFatalError,
    BlobFatalError,
    StreamFatalError,
    CacheFatalError,
    CoderFatalError,
    FilterFatalError,
    ModuleFatalError,
    DrawFatalError,
    ImageFatalError,
    WandFatalError,
    RandomFatalError,
    XServerFatalError,
    MonitorFatalError,
    RegistryFatalError,
    ConfigureFatalError,
    PolicyFatalError,
    ...
} ExceptionType;

typedef struct {
    ExceptionType severity;

    char *reason;
    ...;
} ExceptionInfo;

typedef void (*ErrorHandler)(const ExceptionType, const char *, const char *);
typedef void (*FatalErrorHandler)(const ExceptionType, const char *, const char *);
typedef void (*WarningHandler)(const ExceptionType, const char *, const char *);

ExceptionInfo *AcquireExceptionInfo(void);
ExceptionInfo *DestroyExceptionInfo(ExceptionInfo *);
FatalErrorHandler SetFatalErrorHandler(FatalErrorHandler);
ErrorHandler SetErrorHandler(ErrorHandler);
WarningHandler SetWarningHandler(WarningHandler);


// -----------------------------------------------------------------------------
// magick.h

typedef enum {
    UndefinedFormatType,
    ImplicitFormatType,
    ExplicitFormatType,
    ...
} MagickFormatType;

typedef enum {
    NoThreadSupport,
    DecoderThreadSupport,
    EncoderThreadSupport,
    ...
} MagickThreadSupport;

typedef Image *DecodeImageHandler(const ImageInfo *, ExceptionInfo *);
typedef MagickBooleanType EncodeImageHandler(const ImageInfo *, Image *);
typedef MagickBooleanType IsImageFormatHandler(const unsigned char *, const size_t);

typedef struct {
    char *name;
    char *description;
    char *version;
    char *note;
    char *module;

    DecodeImageHandler *decoder;
    EncodeImageHandler *encoder;
    IsImageFormatHandler *magick;

    MagickBooleanType adjoin;
    MagickBooleanType raw;
    MagickBooleanType endian_support;
    MagickBooleanType blob_support;
    MagickBooleanType seekable_stream;

    //MagickFormatType format_type;
    MagickStatusType thread_support;
    MagickBooleanType stealth;
    ...;
} MagickInfo;

const MagickInfo **GetMagickInfoList(const char *, size_t *, ExceptionInfo *);
void MagickCoreGenesis(const char *, const MagickBooleanType);
void MagickCoreTerminus();


// -----------------------------------------------------------------------------
// geometry.h
// (done)

typedef enum {
    ForgetGravity,
    NorthWestGravity,
    NorthGravity,
    NorthEastGravity,
    WestGravity,
    CenterGravity,
    EastGravity,
    SouthWestGravity,
    SouthGravity,
    SouthEastGravity,
    ...
} GravityType;

typedef struct {
    double sx;
    double rx;
    double ry;
    double sy;
    double tx;
    double ty;
} AffineMatrix;

typedef struct {
    double rho;
    double sigma;
    double xi;
    double psi;
    double chi;
} GeometryInfo;

typedef struct {
    ssize_t x;
    ssize_t y;
} OffsetInfo;

typedef struct {
    size_t width;
    size_t height;
    ssize_t x;
    ssize_t y;
} RectangleInfo;

MagickStatusType GetGeometry(const char *,ssize_t *,ssize_t *,size_t *,size_t *);
char *GetPageGeometry(const char *);
void GravityAdjustGeometry(const size_t,const size_t, const GravityType,RectangleInfo *);
MagickBooleanType IsGeometry(const char *);
MagickBooleanType IsSceneGeometry(const char *,const MagickBooleanType);
MagickStatusType ParseAbsoluteGeometry(const char *,RectangleInfo *);
MagickStatusType ParseAffineGeometry(const char *,AffineMatrix *,ExceptionInfo *);
MagickStatusType ParseGeometry(const char *,GeometryInfo *);
MagickStatusType ParseGravityGeometry(const Image *,const char *,RectangleInfo *, ExceptionInfo *);
MagickStatusType ParseMetaGeometry(const char *,ssize_t *,ssize_t *,size_t *,size_t *);
MagickStatusType ParsePageGeometry(const Image *,const char *,RectangleInfo *,ExceptionInfo *);
MagickStatusType ParseRegionGeometry(const Image *,const char *,RectangleInfo *, ExceptionInfo *);
void SetGeometry(const Image *,RectangleInfo *);
void SetGeometryInfo(GeometryInfo *);


// =============================================================================
// pixel access
// -----------------------------------------------------------------------------
// pixel.h
// (done)

typedef enum {
    UndefinedInterpolatePixel,
    AverageInterpolatePixel,           /* Average 4 nearest neighbours */
    BicubicInterpolatePixel,           /* Catmull-Rom interpolation */
    BilinearInterpolatePixel,          /* Triangular filter interpolation */
    FilterInterpolatePixel,            /* Use resize filter - (very slow) */
    IntegerInterpolatePixel,           /* Integer (floor) interpolation */
    MeshInterpolatePixel,              /* Triangular mesh interpolation */
    NearestNeighborInterpolatePixel,   /* Nearest neighbour only */
    SplineInterpolatePixel,            /* Cubic Spline (blurred) interpolation */
    Average9InterpolatePixel,          /* Average 9 nearest neighbours */
    Average16InterpolatePixel,         /* Average 16 nearest neighbours */
    BlendInterpolatePixel,             /* blend of nearest 1, 2 or 4 pixels */
    BackgroundInterpolatePixel,        /* just return background color */
    CatromInterpolatePixel,            /* Catmull-Rom interpolation */
    ...
} InterpolatePixelMethod;

typedef enum {
    PixelRed,
    PixelCyan,
    PixelGray,
    PixelY,
    PixelGreen,
    PixelMagenta,
    PixelCb,
    PixelBlue,
    PixelYellow,
    PixelCr,
    PixelAlpha,
    PixelBlack,
    PixelIndex,
    MaskPixelComponent,
    ...
} PixelComponent;

typedef enum {
    UndefinedPixelIntensityMethod,
    AveragePixelIntensityMethod,
    BrightnessPixelIntensityMethod,
    LightnessPixelIntensityMethod,
    Rec601LumaPixelIntensityMethod,
    Rec601LuminancePixelIntensityMethod,
    Rec709LumaPixelIntensityMethod,
    Rec709LuminancePixelIntensityMethod,
    RMSPixelIntensityMethod,
    MSPixelIntensityMethod,
    ...
} PixelIntensityMethod;

typedef struct {
    double red;
    double green;
    double blue;
    double opacity;
    double index;
} DoublePixelPacket;

typedef struct {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned int opacity;
    unsigned int index;
} LongPixelPacket;

typedef struct {
    //ClassType storage_class;
    //ColorspaceType colorspace;
    MagickBooleanType matte;
    double fuzz;
    size_t depth;

    ...;
} MagickPixelPacket;

// Quantum is of varying size, which cffi cannot handle.  _api.c contains some
// helpers for dealing with this.
typedef Quantum IndexPacket;

typedef struct {
    ...;
} PixelPacket;

typedef struct {
    ...;
} QuantumPixelPacket;

MagickPixelPacket *CloneMagickPixelPacket(const MagickPixelPacket *);
//MagickRealType DecodePixelGamma(const MagickRealType);
//MagickRealType EncodePixelGamma(const MagickRealType);
//MagickBooleanType ExportImagePixels(const Image *, const ssize_t, const ssize_t, const size_t, const size_t, const char *, const StorageType, void *, ExceptionInfo *);
void GetMagickPixelPacket(const Image *, MagickPixelPacket *);
//MagickRealType GetPixelIntensity(const Image *image, const PixelPacket *);
//MagickBooleanType ImportImagePixels(Image *, const ssize_t, const ssize_t, const size_t, const size_t, const char *, const StorageType, const void *);
MagickBooleanType InterpolateMagickPixelPacket(const Image *, const CacheView *, const InterpolatePixelMethod, const double, const double, MagickPixelPacket *, ExceptionInfo *);


// =============================================================================
// the important stuff
// -----------------------------------------------------------------------------
// image.h

// TODO some defines for opacity up here

typedef enum {
    UndefinedAlphaChannel,
    ActivateAlphaChannel,
    BackgroundAlphaChannel,
    CopyAlphaChannel,
    DeactivateAlphaChannel,
    ExtractAlphaChannel,
    OpaqueAlphaChannel,
    SetAlphaChannel,
    ShapeAlphaChannel,
    TransparentAlphaChannel,
    FlattenAlphaChannel,
    RemoveAlphaChannel,
    ...
} AlphaChannelType;

typedef enum {
    ...
} ImageType;

typedef enum {
    ...
} InterlaceType;

typedef enum {
    ...
} OrientationType;

typedef enum {
    ...
} ResolutionType;

typedef enum {
    ...
} PrimaryInfo;

typedef struct {
    double x1;
    double y1;
    double x2;
    double y2;
} SegmentInfo;

typedef enum {
    ...
} TransmitType;

typedef enum {
    ...
} ChromaticityInfo;


struct _Image {
    ClassType storage_class;

    MagickBooleanType matte;

    size_t columns;
    size_t rows;
    size_t depth;
    size_t colors;

    PixelPacket *colormap;

    RectangleInfo page;

    char magick[];
    char filename[];

    ExceptionInfo exception;

    Image *previous;
    Image *list;
    Image *next;

    ImageType type;

    void *cache;

    ...;
};

struct _ImageInfo {

    MagickBooleanType adjoin;

    FILE *file;

    char magick[];
    char filename[];
    ...;
};


ImageInfo *AcquireImageInfo();
Image *CloneImage(const Image *, const size_t, const size_t, const MagickBooleanType, ExceptionInfo *);
ImageInfo *CloneImageInfo(const ImageInfo *);
ImageInfo *DestroyImageInfo(ImageInfo *);
Image *NewMagickImage(const ImageInfo *, const size_t, const size_t, const MagickPixelPacket *);
Image *ReferenceImage(Image *);
Image *DestroyImage(Image *);


// -----------------------------------------------------------------------------
// list.h
// (done)

void AppendImageToList(Image **, const Image *);
Image *CloneImageList(const Image *, ExceptionInfo *);
Image *CloneImages(const Image *, const char *, ExceptionInfo *);
void DeleteImageFromList(Image **);
void DeleteImages(Image **,const char *, ExceptionInfo *);
Image *DestroyImageList(Image *);
Image *DuplicateImages(Image *, const size_t, const char *, ExceptionInfo *);
Image *GetFirstImageInList(const Image *);
Image *GetImageFromList(const Image *, const ssize_t);
ssize_t GetImageIndexInList(const Image *);
size_t GetImageListLength(const Image *);
Image *GetLastImageInList(const Image *);
Image *GetNextImageInList(const Image *);
Image *GetPreviousImageInList(const Image *);
Image **ImageListToArray(const Image *, ExceptionInfo *);
void InsertImageInList(Image **, Image *);
Image *NewImageList();
void PrependImageToList(Image **, Image *);
Image *RemoveImageFromList(Image **);
Image *RemoveLastImageFromList(Image **);
Image *RemoveFirstImageFromList(Image **);
void ReplaceImageInList(Image **, Image *);
void ReplaceImageInListReturnLast(Image **, Image *);
void ReverseImageList(Image **);
Image *SpliceImageIntoList(Image **, const size_t, const Image *);
Image *SplitImageList(Image *);
void SyncImageList(Image *);
Image *SyncNextImageInList(const Image *);


// =============================================================================
// color
// -----------------------------------------------------------------------------
// colorspace.h
// (done)

typedef enum {
  UndefinedColorspace,
  RGBColorspace,            /* Linear RGB colorspace */
  GRAYColorspace,           /* greyscale (linear) image (faked 1 channel) */
  TransparentColorspace,
  OHTAColorspace,
  LabColorspace,
  XYZColorspace,
  YCbCrColorspace,
  YCCColorspace,
  YIQColorspace,
  YPbPrColorspace,
  YUVColorspace,
  CMYKColorspace,           /* negared linear RGB with black separated */
  sRGBColorspace,           /* Default: non-lienar sRGB colorspace */
  HSBColorspace,
  HSLColorspace,
  HWBColorspace,
  Rec601LumaColorspace,
  Rec601YCbCrColorspace,
  Rec709LumaColorspace,
  Rec709YCbCrColorspace,
  LogColorspace,
  CMYColorspace,            /* negated linear RGB colorspace */
  LuvColorspace,
  HCLColorspace,
  LCHColorspace,            /* alias for LCHuv */
  LMSColorspace,
  LCHabColorspace,          /* Cylindrical (Polar) Lab */
  LCHuvColorspace,          /* Cylindrical (Polar) Luv */
  scRGBColorspace,
  HSIColorspace,
  HSVColorspace,            /* alias for HSB */
  HCLpColorspace,
  YDbDrColorspace
} ColorspaceType;

MagickBooleanType RGBTransformImage(Image *, const ColorspaceType);
MagickBooleanType SetImageColorspace(Image *, const ColorspaceType);
MagickBooleanType TransformImageColorspace(Image *, const ColorspaceType);
MagickBooleanType TransformRGBImage(Image *, const ColorspaceType);


// -----------------------------------------------------------------------------
// color.h
// (not done)

MagickBooleanType QueryColorDatabase(const char *, PixelPacket *, ExceptionInfo *);


// -----------------------------------------------------------------------------
// cache-view.h
// (done)

typedef enum {
  UndefinedVirtualPixelMethod,
  BackgroundVirtualPixelMethod,
  ConstantVirtualPixelMethod,  /* deprecated */
  DitherVirtualPixelMethod,
  EdgeVirtualPixelMethod,
  MirrorVirtualPixelMethod,
  RandomVirtualPixelMethod,
  TileVirtualPixelMethod,
  TransparentVirtualPixelMethod,
  MaskVirtualPixelMethod,
  BlackVirtualPixelMethod,
  GrayVirtualPixelMethod,
  WhiteVirtualPixelMethod,
  HorizontalTileVirtualPixelMethod,
  VerticalTileVirtualPixelMethod,
  HorizontalTileEdgeVirtualPixelMethod,
  VerticalTileEdgeVirtualPixelMethod,
  CheckerTileVirtualPixelMethod
} VirtualPixelMethod;

CacheView *AcquireAuthenticCacheView(const Image *, ExceptionInfo *);
CacheView *AcquireCacheView(const Image *);
CacheView *AcquireVirtualCacheView(const Image *, ExceptionInfo *);
CacheView *CloneCacheView(const CacheView *);
CacheView *DestroyCacheView(CacheView *);

ClassType GetCacheViewStorageClass(const CacheView *);

ColorspaceType GetCacheViewColorspace(const CacheView *);

//const IndexPacket *GetCacheViewVirtualIndexQueue(const CacheView *);

const PixelPacket *GetCacheViewVirtualPixels(const CacheView *, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo *);
const PixelPacket *GetCacheViewVirtualPixelQueue(const CacheView *);

ExceptionInfo *GetCacheViewException(const CacheView *);

//IndexPacket *GetCacheViewAuthenticIndexQueue(CacheView *);

MagickBooleanType GetOneCacheViewVirtualPixel(const CacheView *, const ssize_t, const ssize_t, PixelPacket *, ExceptionInfo *);
MagickBooleanType GetOneCacheViewVirtualMethodPixel(const CacheView *, const VirtualPixelMethod, const ssize_t, const ssize_t, PixelPacket *, ExceptionInfo *);
MagickBooleanType GetOneCacheViewAuthenticPixel(const CacheView *, const ssize_t, const ssize_t, PixelPacket *, ExceptionInfo *);
MagickBooleanType SetCacheViewStorageClass(CacheView *, const ClassType);
MagickBooleanType SetCacheViewVirtualPixelMethod(CacheView *, const VirtualPixelMethod);
MagickBooleanType SyncCacheViewAuthenticPixels(CacheView *, ExceptionInfo *);

MagickSizeType GetCacheViewExtent(const CacheView *);

size_t GetCacheViewChannels(const CacheView *);

PixelPacket *GetCacheViewAuthenticPixelQueue(CacheView *);
PixelPacket *GetCacheViewAuthenticPixels(CacheView *, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo *);
PixelPacket *QueueCacheViewAuthenticPixels(CacheView *, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo *);


// =============================================================================
// whole-image manipulation
// -----------------------------------------------------------------------------
// channel.h

Image *CombineImages(const Image *, const ChannelType, ExceptionInfo *);
//Image *SeparateImage(const Image *, const ChannelType, ExceptionInfo *);
//Image *SeparateImages(const Image *, const ChannelType, ExceptionInfo *);


MagickBooleanType GetImageAlphaChannel(const Image *);
//MagickBooleanType SeparateImageChannel(Image *, const ChannelType);
MagickBooleanType SetImageAlphaChannel(Image *, const AlphaChannelType);

// -----------------------------------------------------------------------------
// resample.h

typedef enum {
    UndefinedFilter,
    PointFilter,
    BoxFilter,
    TriangleFilter,
    HermiteFilter,
    HanningFilter,
    HammingFilter,
    BlackmanFilter,
    GaussianFilter,
    QuadraticFilter,
    CubicFilter,
    CatromFilter,
    MitchellFilter,
    JincFilter,
    SincFilter,
    SincFastFilter,
    KaiserFilter,
    WelshFilter,
    ParzenFilter,
    BohmanFilter,
    BartlettFilter,
    LagrangeFilter,
    LanczosFilter,
    LanczosSharpFilter,
    Lanczos2Filter,
    Lanczos2SharpFilter,
    RobidouxFilter,
    RobidouxSharpFilter,
    CosineFilter,
    SplineFilter,
    LanczosRadiusFilter,
    SentinelFilter,  /* a count of all the filters, not a real filter */
    ...
} FilterTypes;


// -----------------------------------------------------------------------------
// resize.h
// (done)

Image *AdaptiveResizeImage(const Image *, const size_t, const size_t, ExceptionInfo *);
//TODO Image *InterpolativeResizeImage(const Image *, const size_t, const size_t, const InterpolatePixelMethod, ExceptionInfo *);
Image *LiquidRescaleImage(const Image *, const size_t, const size_t, const double, const double, ExceptionInfo *);
Image *MagnifyImage(const Image *, ExceptionInfo *);
Image *MinifyImage(const Image *, ExceptionInfo *);
Image *ResampleImage(const Image *, const double, const double, const FilterTypes, const double, ExceptionInfo *);
Image *ResizeImage(const Image *, const size_t, const size_t, const FilterTypes, const double, ExceptionInfo *);
Image *SampleImage(const Image *, const size_t, const size_t, ExceptionInfo *);
Image *ScaleImage(const Image *, const size_t, const size_t, ExceptionInfo *);
Image *ThumbnailImage(const Image *, const size_t, const size_t, ExceptionInfo *);


// -----------------------------------------------------------------------------
// transform.h
// (done)

Image *AutoOrientImage(const Image *, const OrientationType, ExceptionInfo *);
Image *ChopImage(const Image *, const RectangleInfo *, ExceptionInfo *);
Image *ConsolidateCMYKImages(const Image *, ExceptionInfo *);
Image *CropImage(const Image *, const RectangleInfo *, ExceptionInfo *);
Image *CropImageToTiles(const Image *, const char *, ExceptionInfo *);
Image *ExcerptImage(const Image *, const RectangleInfo *, ExceptionInfo *);
Image *ExtentImage(const Image *, const RectangleInfo *, ExceptionInfo *);
Image *FlipImage(const Image *, ExceptionInfo *);
Image *FlopImage(const Image *, ExceptionInfo *);
Image *RollImage(const Image *, const ssize_t, const ssize_t, ExceptionInfo *);
Image *ShaveImage(const Image *, const RectangleInfo *, ExceptionInfo *);
Image *SpliceImage(const Image *, const RectangleInfo *, ExceptionInfo *);
MagickBooleanType TransformImage(Image **, const char *, const char *);
MagickBooleanType TransformImages(Image **, const char *, const char *);
Image *TransposeImage(const Image *, ExceptionInfo *);
Image *TransverseImage(const Image *, ExceptionInfo *);
Image *TrimImage(const Image *, ExceptionInfo *);


// -----------------------------------------------------------------------------
// composite.h
// (done)

typedef enum {
    UndefinedCompositeOp,
    NoCompositeOp,
    ModulusAddCompositeOp,
    AtopCompositeOp,
    BlendCompositeOp,
    BumpmapCompositeOp,
    ChangeMaskCompositeOp,
    ClearCompositeOp,
    ColorBurnCompositeOp,
    ColorDodgeCompositeOp,
    ColorizeCompositeOp,
    CopyBlackCompositeOp,
    CopyBlueCompositeOp,
    CopyCompositeOp,
    CopyCyanCompositeOp,
    CopyGreenCompositeOp,
    CopyMagentaCompositeOp,
    CopyOpacityCompositeOp,
    CopyRedCompositeOp,
    CopyYellowCompositeOp,
    DarkenCompositeOp,
    DstAtopCompositeOp,
    DstCompositeOp,
    DstInCompositeOp,
    DstOutCompositeOp,
    DstOverCompositeOp,
    DifferenceCompositeOp,
    DisplaceCompositeOp,
    DissolveCompositeOp,
    ExclusionCompositeOp,
    HardLightCompositeOp,
    HueCompositeOp,
    InCompositeOp,
    LightenCompositeOp,
    LinearLightCompositeOp,
    LuminizeCompositeOp,
    MinusDstCompositeOp,
    ModulateCompositeOp,
    MultiplyCompositeOp,
    OutCompositeOp,
    OverCompositeOp,
    OverlayCompositeOp,
    PlusCompositeOp,
    ReplaceCompositeOp,
    SaturateCompositeOp,
    ScreenCompositeOp,
    SoftLightCompositeOp,
    SrcAtopCompositeOp,
    SrcCompositeOp,
    SrcInCompositeOp,
    SrcOutCompositeOp,
    SrcOverCompositeOp,
    ModulusSubtractCompositeOp,
    ThresholdCompositeOp,
    XorCompositeOp,
    DivideDstCompositeOp,
    DistortCompositeOp,
    BlurCompositeOp,
    PegtopLightCompositeOp,
    VividLightCompositeOp,
    PinLightCompositeOp,
    LinearDodgeCompositeOp,
    LinearBurnCompositeOp,
    MathematicsCompositeOp,
    DivideSrcCompositeOp,
    MinusSrcCompositeOp,
    DarkenIntensityCompositeOp,
    LightenIntensityCompositeOp
} CompositeOperator;

MagickBooleanType CompositeImage(Image *,const CompositeOperator,const Image *,const ssize_t, const ssize_t);
MagickBooleanType CompositeImageChannel(Image *,const ChannelType,const CompositeOperator, const Image *,const ssize_t,const ssize_t);
MagickBooleanType TextureImage(Image *,const Image *);


// -----------------------------------------------------------------------------
// fx.h
// (not done)

Image *ColorizeImage(const Image *, const char *, const PixelPacket, ExceptionInfo *);


// -----------------------------------------------------------------------------
// type.h -- as in font faces, not C types

typedef enum {
    UndefinedStretch,
    NormalStretch,
    UltraCondensedStretch,
    ExtraCondensedStretch,
    CondensedStretch,
    SemiCondensedStretch,
    SemiExpandedStretch,
    ExpandedStretch,
    ExtraExpandedStretch,
    UltraExpandedStretch,
    AnyStretch
} StretchType;

typedef enum {
    UndefinedStyle,
    NormalStyle,
    ItalicStyle,
    ObliqueStyle,
    AnyStyle
} StyleType;

typedef struct {
    size_t face;
    char *path;
    char *name;
    char *description;
    char *family;
    StyleType style;
    StretchType stretch;
    size_t weight;
    char *encoding;
    char *foundry;
    char *format;
    char *metrics;
    char *glyphs;

    MagickBooleanType stealth;

    // also some internal linked-list and debug stuff
    ...;
} TypeInfo;


const TypeInfo *GetTypeInfo(const char *,ExceptionInfo *);
const TypeInfo *GetTypeInfoByFamily(const char *,const StyleType,const StretchType, const size_t,ExceptionInfo *);
const TypeInfo **GetTypeInfoList(const char *,size_t *,ExceptionInfo *);
char **GetTypeList(const char *,size_t *,ExceptionInfo *);
MagickBooleanType ListTypeInfo(FILE *,ExceptionInfo *);
MagickBooleanType TypeComponentGenesis();
void TypeComponentTerminus();


// -----------------------------------------------------------------------------
// draw.h
// (not done)

typedef enum {
    UndefinedAlign,
    LeftAlign,
    CenterAlign,
    RightAlign
} AlignType;

typedef enum {
    UndefinedPathUnits,
    UserSpace,
    UserSpaceOnUse,
    ObjectBoundingBox
} ClipPathUnits;

typedef enum {
    UndefinedDecoration,
    NoDecoration,
    UnderlineDecoration,
    OverlineDecoration,
    LineThroughDecoration
} DecorationType;

typedef enum {
    UndefinedDirection,
    RightToLeftDirection,
    LeftToRightDirection
} DirectionType;

typedef enum {
    UndefinedRule,
    EvenOddRule,
    NonZeroRule
} FillRule;

typedef enum {
    UndefinedGradient,
    LinearGradient,
    RadialGradient
} GradientType;

typedef enum {
    UndefinedCap,
    ButtCap,
    RoundCap,
    SquareCap
} LineCap;

typedef enum {
    UndefinedJoin,
    MiterJoin,
    RoundJoin,
    BevelJoin
} LineJoin;

typedef enum {
    UndefinedMethod,
    PointMethod,
    ReplaceMethod,
    FloodfillMethod,
    FillToBorderMethod,
    ResetMethod
} PaintMethod;

typedef enum {
    UndefinedPrimitive,
    PointPrimitive,
    LinePrimitive,
    RectanglePrimitive,
    RoundRectanglePrimitive,
    ArcPrimitive,
    EllipsePrimitive,
    CirclePrimitive,
    PolylinePrimitive,
    PolygonPrimitive,
    BezierPrimitive,
    ColorPrimitive,
    MattePrimitive,
    TextPrimitive,
    ImagePrimitive,
    PathPrimitive
} PrimitiveType;

typedef enum {
    UndefinedReference,
    GradientReference
} ReferenceType;

typedef enum {
    UndefinedSpread,
    PadSpread,
    ReflectSpread,
    RepeatSpread
} SpreadMethod;

typedef struct {
    double x;
    double y;
} PointInfo;

typedef struct {
    MagickPixelPacket color;
    MagickRealType offset;
} StopInfo;

typedef struct {
    GradientType type;
    RectangleInfo bounding_box;
    SegmentInfo gradient_vector;
    StopInfo *stops;
    size_t number_stops;
    SpreadMethod spread;
    PointInfo center;
    MagickRealType radius;
} GradientInfo;

typedef struct _ElementReference {
    char *id;
    ReferenceType type;
    GradientInfo gradient;
    size_t signature;
    struct _ElementReference *previous;
    struct _ElementReference *next;
} ElementReference;

typedef struct {
    char *primitive;
    char *geometry;
    RectangleInfo viewbox;
    AffineMatrix affine;
    GravityType gravity;
    PixelPacket fill;
    PixelPacket stroke;
    double stroke_width;
    GradientInfo gradient;
    Image *fill_pattern;
    Image *tile;
    Image *stroke_pattern;
    MagickBooleanType stroke_antialias;
    MagickBooleanType text_antialias;
    FillRule fill_rule;
    LineCap linecap;
    LineJoin linejoin;
    size_t miterlimit;
    double dash_offset;
    DecorationType decorate;
    CompositeOperator compose;
    char *text;
    size_t face;
    char *font;
    char *metrics;
    char *family;
    StyleType style;
    StretchType stretch;
    size_t weight;
    char *encoding;
    double pointsize;
    char *density;
    AlignType align;
    PixelPacket undercolor;
    PixelPacket border_color;
    char *server_name;
    double *dash_pattern;
    char *clip_mask;
    SegmentInfo bounds;
    ClipPathUnits clip_units;
    Quantum opacity;
    MagickBooleanType render;
    ElementReference element_reference;
    MagickBooleanType debug;
    size_t signature;
    double kerning;
    double interword_spacing;
    double interline_spacing;
    DirectionType direction;
    ...;
} DrawInfo;

typedef struct {
    PointInfo point;
    size_t coordinates;
    PrimitiveType primitive;
    PaintMethod method;
    char *text;
} PrimitiveInfo;

typedef struct {
    PointInfo pixels_per_em;
    double ascent;
    double descent;
    double width;
    double height;
    double max_advance;
    double underline_position;
    double underline_thickness;
    SegmentInfo bounds;
    PointInfo origin;
} TypeMetric;

DrawInfo *AcquireDrawInfo();
DrawInfo *CloneDrawInfo(const ImageInfo *,const DrawInfo *);
DrawInfo *DestroyDrawInfo(DrawInfo *);
MagickBooleanType DrawAffineImage(Image *,const Image *,const AffineMatrix *);
MagickBooleanType DrawClipPath(Image *,const DrawInfo *,const char *);
MagickBooleanType DrawGradientImage(Image *,const DrawInfo *);
MagickBooleanType DrawImage(Image *,const DrawInfo *);
MagickBooleanType DrawPatternPath(Image *,const DrawInfo *,const char *,Image **);
MagickBooleanType DrawPrimitive(Image *,const DrawInfo *,const PrimitiveInfo *);
void GetAffineMatrix(AffineMatrix *);
void GetDrawInfo(const ImageInfo *, DrawInfo *);


// -----------------------------------------------------------------------------
// paint.h
// (not done)

MagickBooleanType OpaquePaintImage(Image *, const MagickPixelPacket *, const MagickPixelPacket *, const MagickBooleanType);


// =============================================================================
// i/o
// -----------------------------------------------------------------------------
// stream.h
// (done)

typedef size_t (*StreamHandler)(const Image *, const void *, const size_t);

Image *ReadStream(const ImageInfo *, StreamHandler, ExceptionInfo *);
MagickBooleanType WriteStream(const ImageInfo *, Image *, StreamHandler);


// -----------------------------------------------------------------------------
// blob.h
// (done)

static const int MagickMaxBufferExtent;

typedef enum {
    ReadMode,
    WriteMode,
    IOMode
} MapMode;

MagickBooleanType BlobToFile(char *, const void *, const size_t, ExceptionInfo *);
Image *BlobToImage(const ImageInfo *, const void *, const size_t, ExceptionInfo *);
void DestroyBlob(Image *);
void DuplicateBlob(Image *, const Image *);
unsigned char *FileToBlob(const char *, const size_t, size_t *, ExceptionInfo *);
MagickBooleanType FileToImage(Image *, const char *);
MagickBooleanType GetBlobError(const Image *);
FILE *GetBlobFileHandle(const Image *);
//MagickSizeType GetBlobSize(const Image *);
unsigned char *GetBlobStreamData(const Image *);
StreamHandler GetBlobStreamHandler(const Image *);
unsigned char *ImageToBlob(const ImageInfo *, Image *, size_t *, ExceptionInfo *);
MagickBooleanType ImageToFile(Image *, char *, ExceptionInfo *);
unsigned char *ImagesToBlob(const ImageInfo *, Image *, size_t *, ExceptionInfo *);
MagickBooleanType InjectImageBlob(const ImageInfo *, Image *, Image *, const char *, ExceptionInfo *);
MagickBooleanType IsBlobExempt(const Image *);
MagickBooleanType IsBlobSeekable(const Image *);
MagickBooleanType IsBlobTemporary(const Image *);
Image *PingBlob(const ImageInfo *, const void *, const size_t, ExceptionInfo *);
void SetBlobExempt(Image *, const MagickBooleanType);


// -----------------------------------------------------------------------------
// constitute.h

typedef enum {
    UndefinedPixel,
    CharPixel,
    DoublePixel,
    FloatPixel,
    IntegerPixel,
    LongPixel,
    QuantumPixel,
    ShortPixel
} StorageType;

MagickBooleanType ConstituteComponentGenesis();
void ConstituteComponentTerminus();
Image *ConstituteImage(const size_t, const size_t, const char *, const StorageType, const void *, ExceptionInfo *);
Image *PingImage(const ImageInfo *, ExceptionInfo *);
Image *PingImages(const ImageInfo *, ExceptionInfo *);
Image *ReadImage(const ImageInfo *, ExceptionInfo *);
Image *ReadImages(const ImageInfo *, ExceptionInfo *);
Image *ReadInlineImage(const ImageInfo *, const char *, ExceptionInfo *);
MagickBooleanType WriteImage(const ImageInfo *, Image *);
MagickBooleanType WriteImages(const ImageInfo *, Image *, const char *, ExceptionInfo *);


// -----------------------------------------------------------------------------
// layer.h

Image *CoalesceImages(Image *, ExceptionInfo *);
Image *OptimizeImageLayers(Image *, ExceptionInfo *);
void OptimizeImageTransparency(Image *, ExceptionInfo *);


// =============================================================================
// custom non-imagemagick stuff implemented in _api.c

MagickRealType sanpera_to_magick_real_type(long double);
Quantum sanpera_to_quantum(long double);
void sanpera_pixel_to_doubles(PixelPacket *, double[]);
void sanpera_pixel_from_doubles(PixelPacket *, double[]);
void sanpera_pixel_from_doubles_channel(PixelPacket *, double[], ChannelType);
void sanpera_magick_pixel_to_doubles(MagickPixelPacket *, double[]);
void sanpera_magick_pixel_from_doubles(MagickPixelPacket *, double[]);
void sanpera_magick_pixel_from_doubles_channel(MagickPixelPacket *, double[], ChannelType);

typedef enum {
    SANPERA_OP_LOAD_SOURCE_COLOR,
    SANPERA_OP_LOAD_COLOR,
    SANPERA_OP_LOAD_NUMBER,
    SANPERA_OP_ADD,
    SANPERA_OP_MULTIPLY,
    SANPERA_OP_CLAMP,
    SANPERA_OP_DONE
} sanpera_evaluate_op;

typedef struct {
    sanpera_evaluate_op op;
    PixelPacket *color;
    double number;
} sanpera_evaluate_step;

Image *sanpera_evaluate_filter(Image **, sanpera_evaluate_step[], ChannelType, ExceptionInfo *);
