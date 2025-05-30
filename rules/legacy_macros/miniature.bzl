def miniature(name, src, size = "100x100", **kwargs):
    """Create a miniature of the src image.

    The generated file is prefixed with 'small_'.
    """
    native.genrule(
        name = name,
        srcs = [src],
        # Note that the line below will fail if `src` is not a filename string
        outs = ["small_" + src],
        # cmd = "convert $< -resize " + size + " $@",
        cmd = "echo $< " + size + "> $@",
        **kwargs
    )
